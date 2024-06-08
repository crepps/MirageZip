#include "miragezip.h"

unsigned int MirageZip::CreateAppData()
{
    std::string path{ getenv("LOCALAPPDATA") };

    path += "\\MirageZip";
    archivePath = path + "\\archive.zip";
    stat(path.c_str(), &Statinfo);

    // If directory doesn't exist, create it
    if (!(Statinfo.st_mode & S_IFDIR))
    {
        std::error_code err;
        
        err.clear();
        if (!std::filesystem::create_directories(path, err))
            return FAILURE_ABORT;
    }

    return SUCCESS;
}
void MirageZip::SetError(const std::string& arg) noexcept
{
    error = arg;
}
std::string MirageZip::GetError() const noexcept
{
    return error;
}
void MirageZip::SetPath(Path type, const std::string& path) noexcept
{
    switch (type)
    {
    case IMAGE:
        imagePath = path;
        break;

    case FILE:
        filePath = path;
        break;

    case EXPORT:
        exportPath = path;
    }
}
unsigned int MirageZip::TestPassword(const std::string& pw) const noexcept
{
    char lowerSet[]{ "abcdefghijklmnopqrstuvwxyz" },
        upperSet[]{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
        numberSet[]{ "0123456789" },
        charSet[]{ "!@#$%^&*()-_=+,.<>/?|[]{}:;~\'\"\\" };
    bool found[NUM_SETS]{ false, false, false, false };
    float points{ 0.0f };

    // Test for lowercase, uppercase, numbers and special characters
    for (auto& c : pw)
    {
        if (!found[LOWER])
        {
            if (strchr(lowerSet, c))
            {
                points += 0.5f;
                found[LOWER] = true;
            }
        }
        if (!found[UPPER])
        {
            if (strchr(upperSet, c))
            {
                points += 0.5f;
                found[UPPER] = true;
            }
        }
        if (!found[NUMBERS])
        {
            if (strchr(numberSet, c))
            {
                points += 0.5f;
                found[NUMBERS] = true;
            }
        }
        if (!found[CHARACTERS])
        {
            if (strchr(charSet, c))
            {
                points += 0.5f;
                found[CHARACTERS] = true;
            }
        }
    }

    // Test password length
    if (pw.length() >= MEDIUM_LENGTH && pw.length() < STRONG_LENGTH && points >= 1.5f)
        ++points;

    else if (pw.length() >= STRONG_LENGTH && points >= 1.0f)
        points += 2;

    return (unsigned int)points;
}
void MirageZip::SetPassword(const std::string& pw) noexcept
{
    password = pw;
}
unsigned int MirageZip::ZipFile()
{
    // Create archive and open
    std::remove(archivePath.c_str());
    int errCode = 0;
    zip* archive = zip_open(archivePath.c_str(), ZIP_CREATE, &errCode);
    if (!archive) return FAILURE_ABORT;

    // Open file, get size
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return FAILURE_ABORT;
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Store file data in buffer, close file
    fileData = new char[fileSize];
    file.read(fileData, fileSize);
    file.close();

    // Get filename from file path
    std::string fileName(filePath);
    size_t strPos = fileName.find_last_of("\\");
    fileName.erase(0, strPos + 1);

    // Zip file using buffer, close archive
    zip_source_t* source;
    source = zip_source_buffer(archive, fileData, fileSize, 0);
    if (!source) return FAILURE_ABORT;
    zip_file_add(archive, fileName.c_str(), source, 0);

    if (password != "\0")
        zip_file_set_encryption(archive, 0, ZIP_EM_AES_256, password.c_str());

    zip_close(archive);

    return SUCCESS;
}
unsigned int MirageZip::Concatenate() const
{
    STARTUPINFOA info{ sizeof(info) };
    PROCESS_INFORMATION processInfo;
    std::stringstream cmd{ "" };
    cmd << "/c COPY /B \"" << imagePath << "\" + \"" << archivePath << "\" \"" << exportPath << "\"";

    if (CreateProcessA("C:\\Windows\\System32\\cmd.exe", cmd.str().data(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        return SUCCESS;
    }

    return FAILURE_ABORT;
}
const char* MirageZip::GetArchivePath() const noexcept
{
    return archivePath.c_str();
}

// -- External --
unsigned int HideFile(MirageZip* obj)
{
    try
    {
        obj->ZipFile();
    }
    catch (const std::exception& e)
    {
        obj->SetError(e.what());
        return FAILURE_ABORT;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to zip file.");
        return FAILURE_ABORT;
    }
    try
    {
        obj->Concatenate();
    }
    catch (const std::exception& e)
    {
        obj->SetError(e.what());
        return FAILURE_ABORT;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to concatenate files.");
        return FAILURE_ABORT;
    }
    try
    {
        std::remove(obj->GetArchivePath());
    }
    catch (const std::exception& e)
    {
        obj->SetError(e.what());
        return FAILURE_CONTINUE;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to remove temp archive.");
        return FAILURE_CONTINUE;
    }

    return SUCCESS;
}
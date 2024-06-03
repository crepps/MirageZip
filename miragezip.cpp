#include "miragezip.h"

MirageZip::MirageZip()
{
    password = "\0";

    CreateAppData();
}
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
            return 1;
    }

    return 0;
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
    char lower[]{ "abcdefghijklmnopqrstuvwxyz" },
        upper[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        numbers[]{"0123456789"},
        chars[]{"!@#$%^&*()-_=+,.<>/?|[]{}:;~\'\"\\"};
    bool found[4]{ false, false, false, false };
    float points{ 0.0f };

    // Test for lowercase, uppercase, numbers and special characters
    for (auto& c : pw)
    {
        if (!found[0])
        {
            if (strchr(lower, c))
            {
                points += 0.5f;
                found[0] = true;
            }
        }
        if (!found[1])
        {
            if (strchr(upper, c))
            {
                points += 0.5f;
                found[1] = true;
            }
        }
        if (!found[2])
        {
            if (strchr(numbers, c))
            {
                points += 0.5f;
                found[2] = true;
            }
        }
        if (!found[3])
        {
            if (strchr(chars, c))
            {
                points += 0.5f;
                found[3] = true;
            }
        }
    }

    // Test password length
    if (pw.length() >= 8 && pw.length() < 12 && points >= 1.5f)
        ++points;

    else if (pw.length() >= 12)
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

    // Open file, get size
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Store file data in buffer, close file
    char* data = new char[fileSize];
    file.read(data, fileSize);
    file.close();

    // Get filename from file path
    std::string fileName(filePath);
    size_t strPos = fileName.find_last_of("\\");
    fileName.erase(0, strPos + 1);

    // Zip file using buffer, close archive
    zip_source_t* source;
    source = zip_source_buffer(archive, data, fileSize, 0);
    zip_file_add(archive, fileName.c_str(), source, 0);

    if (password != "\0")
        zip_file_set_encryption(archive, 0, ZIP_EM_AES_256, password.c_str());

    zip_close(archive);

    delete[] data;

    return 0;
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
        return 0;
    }

    return 1;
}
const char* MirageZip::GetArchivePath() const noexcept
{
    return archivePath.c_str();
}
MirageZip::~MirageZip()
{
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
        return 1;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to zip file.");
        return 1;
    }
    try
    {
        obj->Concatenate();
    }
    catch (const std::exception& e)
    {
        obj->SetError(e.what());
        return 1;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to concatenate files.");
        return 1;
    }
    try
    {
        std::remove(obj->GetArchivePath());
    }
    catch (const std::exception& e)
    {
        obj->SetError(e.what());
        return 1;
    }
    catch (...)
    {
        obj->SetError("Exception thrown when attempting to remove temp archive.");
        return 2;
    }

    return 0;
}
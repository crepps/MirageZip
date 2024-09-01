#include "miragezip.h"

void MirageZip::Init()
{
    /* If %LOCALAPPDATA%\MirageZip doesn't exist, and
       attempt to create it fails, notify user and abort */

    if (CreateAppData())
    {
        MessageBoxA(NULL, GetError().c_str(), "Failed to create app data folder.", MB_OK);
        abort();
    }
}
unsigned int MirageZip::CreateAppData()
{
    try
    {
        // Set archivePath member, check whether folder already exists
        std::string path{ getenv("LOCALAPPDATA") };
        path += "\\MirageZip";
        archivePath = path + "\\archive.zip";
        stat(path.c_str(), &Statinfo);

        if (!(Statinfo.st_mode & S_IFDIR))
        {
            // If directory doesn't exist, create it
            std::error_code err;
            err.clear();

            if (!std::filesystem::create_directories(path, err))
            {
                std::stringstream msg("Error code: ");
                msg << err;
                SetError(msg.str());
                return FAILURE_ABORT;
            }
        }

        return SUCCESS;
    }
    catch (...)
    {
        SetError("Exception thrown.");
        return FAILURE_ABORT;
    }
}
void MirageZip::SetPath(PATH_TYPE type, const std::string& path) noexcept
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
    bool found[NUM_SETS]{ false, false, false, false };
    char lowerSet[]{ "abcdefghijklmnopqrstuvwxyz" },
        upperSet[]{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" },
        numberSet[]{ "0123456789" },
        charSet[]{ "!@#$%^&*()-_=+,.<>/?|[]{}:;~\'\"\\" };
    char* sets[NUM_SETS]{ lowerSet, upperSet, numberSet, charSet };
    float points{ 0.0f };

    /* Compare each character in password to each character set if not yet matched,
       add half a point for each character set with one or more instances
       of lowercase, uppercase, digits or special characters in password   */

    for (auto& c : pw)
    {
        for (unsigned char type = LOWER; type < NUM_SETS; ++type)
        {
            if (!found[type])
            {
                if (strchr(sets[type], c))
                {
                    points += 0.5f;
                    found[type] = true;
                }
            }
        }
    }

    // If pass is medium length (less than 12), add one point if at least three character types
    if (pw.length() >= MEDIUM_LENGTH && pw.length() < STRONG_LENGTH && points >= 1.5f)
        ++points;

    // If strong length, add two points if at least two character types
    else if (pw.length() >= STRONG_LENGTH && points >= 1.0f)
        points += 2;

    /*    weak - fewer than three points
        medium - three points
        strong - four points    */

    return (unsigned int)points;
}

unsigned int MirageZip::ZipFile()
{
    /* This function will read file data into a buffer, zip the file using the buffer, and encrypt
       the data using 256-bit AES if a password has been set by the user. Error handling is done in
       HideFile()  */

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

    // Store file data in resource management object, close file
    std::unique_ptr<char[]> fileData(new char[fileSize]);
    file.read(fileData.get(), fileSize);
    file.close();

    // Get filename from file path
    std::string fileName(filePath);
    size_t strPos = fileName.find_last_of("\\");
    fileName.erase(0, strPos + 1);

    // Zip file using buffer
    zip_source_t* source;
    source = zip_source_buffer(archive, fileData.get(), fileSize, 0);
    if (!source) return FAILURE_ABORT;
    zip_file_add(archive, fileName.c_str(), source, 0);


    // Encrypt archive if password was set
    if (password != "\0")
        zip_file_set_encryption(archive, 0, ZIP_EM_AES_256, password.c_str());

    // Close archive
    zip_close(archive);

    return SUCCESS;
}
unsigned int MirageZip::Concatenate() const
{
    /* Execute Windows system command to combine files, e.g.:

       COPY /B <image path> + <archive path> <destination path>

       Error handling is done in HideFile()   */

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

// -- External --
unsigned int HideFile(MirageZip* obj)
{
    //  Attempt to zip selected file
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
        obj->SetError("Exception thrown while attempting to zip file.");
        return FAILURE_ABORT;
    }

    // Attempt to concatenate image and temp archive
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
        obj->SetError("Exception thrown while attempting to concatenate files.");
        return FAILURE_ABORT;
    }

    // Attempt to delete temp archive
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
        obj->SetError("Exception thrown while attempting to remove temp archive.");
        return FAILURE_CONTINUE;
    }

    return SUCCESS;
}
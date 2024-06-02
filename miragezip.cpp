#include "miragezip.h"

MirageZip::MirageZip()
{
    password = "\0";

    CreateAppData();
}
int MirageZip::CreateAppData()
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
void MirageZip::SetError(std::string arg) noexcept
{
    error = arg;
}
std::string MirageZip::GetError() noexcept
{
    return error;
}
void MirageZip::SetPath(Path type, std::string path) noexcept
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
void MirageZip::SetPassword(std::string pw) noexcept
{
    password = pw;
}
class MyException : std::runtime_error
{
public:
    MyException() : std::runtime_error("shit") {}
};
int MirageZip::ZipFile()
{
    throw MyException();
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
int MirageZip::Concatenate()
{
    std::stringstream cmd{ "" };

    cmd << "COPY /B \"" << imagePath << "\" + \"" << archivePath << "\" \"" << exportPath << "\"";

    system(cmd.str().c_str());

    return 0;
}
const char* MirageZip::GetArchivePath() noexcept
{
    return archivePath.c_str();
}
MirageZip::~MirageZip()
{
}

// -- External --
int HideFile(MirageZip* obj)
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
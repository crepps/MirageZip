#include "miragezip.h"

MirageZip::MirageZip()
{
    password = "\0";

    CreateAppData();
}
int MirageZip::CreateAppData()
{
    struct stat info;
    std::string path{ getenv("LOCALAPPDATA") };

    path += "\\MirageZip";
    workingDir = path;
    stat(path.c_str(), &info);

    // If directory doesn't exist, create it
    if (!(info.st_mode & S_IFDIR))
    {
        std::error_code err;
        
        err.clear();
        if (!std::filesystem::create_directories(path, err))
            return 1;
    }

    return 0;
}
void MirageZip::SetPath(Path type, std::string path)
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
void MirageZip::SetPassword(std::string pw)
{
    password = pw;
}
int MirageZip::ZipFile()
{
    // Create archive and open
    std::string archivePath = workingDir + "\\archive.zip";
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
    std::string zipPath{ workingDir + "\\archive.zip"};
    return 0;
}
MirageZip::~MirageZip()
{
}
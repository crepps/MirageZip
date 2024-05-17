#include "mirage.h"

Mirage::Mirage()
{

}
int Mirage::ZipFile()
{
    // Create archive and open
    int errCode = 0;
    zip* archive = zip_open("archive.zip", ZIP_CREATE, &errCode);

    // Open file, get size
    std::ifstream file(filePath, std::ios::binary);
    file.seekg(0, std::ios::end);
    int n = file.tellg();
    file.seekg(0, std::ios::beg);

    // Store file data in buffer, close file
    char* data = new char[n];
    file.read(data, n);
    file.close();

    // Get filename from path
    std::string fileName(filePath);
    size_t strPos = fileName.find_last_of("\\");
    fileName.erase(0, strPos + 1);

    // Zip file using buffer, close archive
    zip_source_t* source;
    source = zip_source_buffer(archive, data, n, 0);
    delete data;
    zip_file_add(archive, fileName.c_str(), source, 0);

    if (password != "\0")
        zip_file_set_encryption(archive, 0, ZIP_EM_AES_256, password.c_str());

    zip_close(archive);

    return 0;
}
int Mirage::Concatenate()
{
    return 0;
}
Mirage::~Mirage()
{
}
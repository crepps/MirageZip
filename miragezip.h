#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include "zip.h"
#include <stdlib.h>

class MirageZip
{
private:
    std::string workingDir,
        imagePath,
        filePath,
        exportPath,
        password;

public:
    enum Path
    {
        IMAGE,
        FILE,
        EXPORT
    };

    MirageZip();
    int CreateAppData();
    void SetPath(Path, std::string);
    void SetPassword(std::string);
    int ZipFile();
    int Concatenate();
    ~MirageZip();
};
#pragma once
#include <sstream>
#include <fstream>
#include <filesystem>
#include "zip.h"
#include <stdlib.h>

class MirageZip
{
private:
    std::string archivePath,
        imagePath,
        filePath,
        exportPath,
        password;

    struct stat Statinfo;

public:
    enum Path
    {
        IMAGE,
        FILE,
        EXPORT
    };

    MirageZip();
    int CreateAppData();
    void SetPath(Path, std::string) noexcept;
    void SetPassword(std::string) noexcept;
    int ZipFile();
    int Concatenate();
    const char* GetArchivePath() noexcept;
    ~MirageZip();
};

extern void HideFile(MirageZip* obj);

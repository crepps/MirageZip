#pragma once
#include <sstream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include "zip.h"
#include <stdlib.h>

class MirageZip
{
private:
    std::string error,
        archivePath,
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
    void SetError(std::string) noexcept;
    std::string GetError() noexcept;
    void SetPath(Path, std::string) noexcept;
    void SetPassword(std::string) noexcept;
    int ZipFile();
    int Concatenate();
    const char* GetArchivePath() noexcept;
    ~MirageZip();
};

extern int HideFile(MirageZip* obj);

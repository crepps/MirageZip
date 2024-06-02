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
    unsigned int CreateAppData();
    void SetError(const std::string&) noexcept;
    std::string GetError() const noexcept;
    void SetPath(Path, const std::string&) noexcept;
    unsigned int TestPassword(const std::string&) const noexcept;
    void SetPassword(const std::string&) noexcept;
    unsigned int ZipFile();
    unsigned int Concatenate() const;
    const char* GetArchivePath() const noexcept;
    ~MirageZip();
};

extern unsigned int HideFile(MirageZip* obj);

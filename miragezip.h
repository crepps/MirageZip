#pragma once
#include <sstream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include "zip.h"

#define WEAK_SCORE 2
#define MEDIUM_SCORE 3
#define STRONG_SCORE 4
#define MEDIUM_LENGTH 8
#define STRONG_LENGTH 12

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

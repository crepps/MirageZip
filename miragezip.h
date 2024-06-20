#pragma once
#include <sstream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <Windows.h>
#include "zip.h"

#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

#define WEAK_SCORE 2
#define MEDIUM_SCORE 3
#define STRONG_SCORE 4
#define MEDIUM_LENGTH 8
#define STRONG_LENGTH 12
#define NUM_SETS 4


class MirageZip
{
private:
    std::string error,
        archivePath,
        imagePath,
        filePath,
        exportPath,
        password;

    struct stat Statinfo;   /* Used for checking whether
                                directory exists with stat() */
    enum CHAR_TYPE
    {
        LOWER,
        UPPER,
        NUMBERS,
        CHARACTERS
    };

public:
    enum PATH_TYPE
    {
        IMAGE,
        FILE,
        EXPORT
    };

    MirageZip() : password("\0") { Init(); }
    void Init();
    unsigned int CreateAppData();
    void SetError(const std::string&) noexcept;
    std::string GetError() const noexcept;
    void SetPath(PATH_TYPE, const std::string&) noexcept;
    unsigned int TestPassword(const std::string&) const noexcept;
    void SetPassword(const std::string&) noexcept;
    unsigned int ZipFile();
    unsigned int Concatenate() const;
    const char* GetArchivePath() const noexcept;
    ~MirageZip() {}
};

extern unsigned int HideFile(MirageZip* obj);

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
        filePath,
        password;

public:
    MirageZip();
    int CreateAppData();
    int ZipFile();
    int Concatenate();
    ~MirageZip();
};
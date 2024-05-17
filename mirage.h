#pragma once
#include <string>
#include <fstream>
#include "zip.h"

class Mirage
{
private:
    std::string filePath,
        password;

public:
    Mirage();
    int ZipFile();
    int Concatenate();
    ~Mirage();
};
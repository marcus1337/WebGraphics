#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>

#ifndef IOSTUFF_H
#define IOSTUFF_H


class IOStuff
{
public:
    std::string binFolderPath;
    std::string shaderPath;
    std::string texturePath;
    std::string normalTexturePath;
    std::string modelsPath;

public:

    IOStuff();
    ~IOStuff();

};

#endif
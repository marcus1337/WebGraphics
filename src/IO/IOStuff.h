#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

#ifndef IOSTUFF_H
#define IOSTUFF_H


class IOStuff
{
private:

public:
    std::string binFolderPath;
    std::string texturePath;
    std::string normalTexturePath;
    std::string modelsPath;

    IOStuff();
    ~IOStuff();
};

#endif
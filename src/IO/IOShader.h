#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include "ShaderData.h"


#ifndef IOSHADER_H
#define IOSHADER_H


class IOShader
{
private:
    std::string binFolderPath;
    std::vector<std::vector<std::string>> getShaderFilenames();
    ShaderCode getShaderCode(const std::string& filename);
    std::string readShaderSource(const std::string& fileName);

    std::string getFileExtension(const std::string& fileName);
    bool isShaderFile(const std::string& fileName);
    bool isFragmentShaderExtension(const std::string& extension);
    bool isVertexShaderExtension(const std::string& extension);
    uint32_t getShaderValue(const std::string& extension);

    void removeExtension(std::string& fileName);

public:
    std::string shaderPath;

    IOShader();
    std::vector<ShaderData> getShaderData();
};

#endif
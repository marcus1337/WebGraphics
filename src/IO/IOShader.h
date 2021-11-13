#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>


#ifndef IOSHADER_H
#define IOSHADER_H


class IOShader
{
private:
    std::string binFolderPath;
    std::vector<std::vector<std::string>> getShaderFilenames();
    std::tuple<std::string, uint32_t> getShaderInfo(const std::string& filename);
    std::string readShaderSource(const std::string& fileName);

    std::string getFileExtension(const std::string& fileName);
    bool isShaderFile(const std::string& fileName);
    bool isFragmentShaderExtension(const std::string& extension);
    bool isVertexShaderExtension(const std::string& extension);
    uint32_t getShaderValue(const std::string& extension);

public:
    std::string shaderPath;

    IOShader();
    std::vector<std::vector<std::tuple<std::string, uint32_t>>> getShaderInfos();
};

#endif
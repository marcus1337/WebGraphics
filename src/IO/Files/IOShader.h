#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>


#ifndef IOSHADER_H
#define IOSHADER_H

struct ShaderCode {
    std::string glslCode;
    uint32_t shaderType;
};

struct ShaderCodeSet {
    std::vector<ShaderCode> shaders;
    std::string name;
};


class IOShader
{
private:
    std::vector<std::vector<std::string>> getShaderFilenames();
    ShaderCode getShaderCode(const std::string& filename);
    std::string readShaderSource(const std::string& fileName);

    std::string getFileExtension(const std::string& fileName);
    bool isShaderFile(const std::string& fileName);
    bool isFragmentShaderExtension(const std::string& extension);
    bool isVertexShaderExtension(const std::string& extension);
    uint32_t getShaderValue(const std::string& extension);

    void removeExtension(std::string& fileName);

    std::vector<ShaderCodeSet> shaderCodeSets;

public:
    std::vector<std::string> getShaderFilePaths();
    IOShader();

    void loadData();
    std::vector<ShaderCodeSet> getShaderCodeSets();
    ShaderCodeSet getShaderCodeSet(std::string name);
    bool shaderCodeSetExist(std::string name);
};

#endif
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <set>


#ifndef IOSHADER_H
#define IOSHADER_H

struct ShaderCode {
    std::string glslCode;
    uint32_t shaderType;
    std::string name;
};

struct ShaderCodeSet {
    std::vector<ShaderCode> shaders;
    std::string name;
};


class IOShader
{
private:
    ShaderCode getShaderCode(std::string shaderFilePath, std::string shaderFileExtension);
    std::string readShaderSource(const std::string& shaderFilePath);
    bool isShaderFile(const std::string& fileName);
    bool isFragmentShaderExtension(const std::string& extension);
    bool isVertexShaderExtension(const std::string& extension);
    uint32_t getShaderValue(const std::string& extension);

    std::vector<ShaderCode> shaderCodes;
    void loadShaderCodeSets();
    std::set<std::string> getShaderCodeNames();
    ShaderCodeSet getShaderCodeSet(std::string shaderName);

public:
    IOShader();
    void loadShaderCode(std::vector<std::string> shaderFilePaths, std::vector<std::string> shaderNames, std::vector<std::string> shaderFileExtensions);    
    std::vector<ShaderCodeSet> shaderCodeSets;

};

#endif
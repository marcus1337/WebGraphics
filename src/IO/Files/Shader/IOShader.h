#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <set>
#include "ShaderCode.h"
#include "ShaderCompiler.h"


#ifndef IOSHADER_H
#define IOSHADER_H

class IOShader
{
private:

    void addDefaultShaderCode();

    ShaderCompiler shaderCompiler;
    std::map<std::string, GLuint> programs;
    void makeProgram(std::vector<ShaderCode> shaderCode, std::string shaderName);
    void deletePrograms();
    std::vector<ShaderCodeSet> shaderCodeSets;

    ShaderCode getShaderCode(std::string shaderFilePath, std::string shaderFileExtension);
    std::string readShaderSource(const std::string& shaderFilePath);
    bool isShaderFile(const std::string& fileName);
    bool isFragmentShaderExtension(const std::string& extension);
    bool isVertexShaderExtension(const std::string& extension);
    uint32_t getShaderValue(const std::string& extension);

public:
    IOShader();
    ~IOShader();

    void loadShaderCode(std::vector<std::string> shaderFilePaths, std::vector<std::string> shaderNames, std::vector<std::string> shaderFileExtensions);    
    GLuint getProgram(std::string name);
    int getNumPrograms();
    void addShaderCode(ShaderCode shaderCode, std::string shaderName);
    void loadPrograms();

};

#endif
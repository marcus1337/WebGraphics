#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <set>
#include "ShaderCode.h"


#ifndef IOSHADER_H
#define IOSHADER_H

class IOShader
{
private:

    void deletePrograms();
    std::map<std::string, GLuint> programs;
    void makeProgram(std::vector<ShaderCode> shaderCode, std::string shaderName);
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

    void clearCodeSets();
    void addDefaultShaderCode();
    void loadShaderCode(std::vector<std::string> shaderFilePaths, std::vector<std::string> shaderNames, std::vector<std::string> shaderFileExtensions);    
    GLuint getProgram(std::string name);
    int getNumPrograms();
    void addShaderCode(ShaderCode shaderCode, std::string shaderName);
    void loadPrograms();

};

#endif
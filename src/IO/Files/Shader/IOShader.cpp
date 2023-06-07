#include "IO/Files/Shader/IOShader.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>
#include "IO/Files/Shader/DefaultShaderCode.h"
#include "IO/Files/Shader/ShaderCompiler.h"

IOShader::IOShader()
{

}

IOShader::~IOShader() {
    deletePrograms();
}

void IOShader::clearCodeSets() {
    shaderCodeSets.clear();
}

void IOShader::addDefaultShaderCode() {
    DefaultShaderCode defaultCode;
    for (ShaderCode shaderCode : defaultCode.getRectangleCode())
        addShaderCode(shaderCode, "rectangle");
    for (ShaderCode shaderCode : defaultCode.getImageCode())
        addShaderCode(shaderCode, "image");
    for (ShaderCode shaderCode : defaultCode.getTextCode())
        addShaderCode(shaderCode, "text");
    for (ShaderCode shaderCode : defaultCode.getModelCode())
        addShaderCode(shaderCode, "model");
}

bool IOShader::isFragmentShaderExtension(const std::string &extension)
{
    return extension == ".frag";
}
bool IOShader::isVertexShaderExtension(const std::string &extension)
{
    return extension == ".vert";
}
uint32_t IOShader::getShaderValue(const std::string &extension)
{
    if (isVertexShaderExtension(extension))
        return GL_VERTEX_SHADER;
    if (isFragmentShaderExtension(extension))
        return GL_FRAGMENT_SHADER;
    return 0;
}

std::string IOShader::readShaderSource(const std::string & shaderFilePath)
{
    std::ifstream file(shaderFilePath);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

ShaderCode IOShader::getShaderCode(std::string shaderFilePath, std::string shaderFileExtension) {
    ShaderCode shaderCode;
    shaderCode.glslCode = readShaderSource(shaderFilePath);
    shaderCode.shaderType = getShaderValue(shaderFileExtension);
    return shaderCode;
}

void IOShader::loadShaderCode(std::vector<std::string> shaderFilePaths, std::vector<std::string> shaderNames, std::vector<std::string> shaderFileExtensions) {
    for (int i = 0; i < shaderNames.size(); i++) {
        std::string shaderFilePath = shaderFilePaths[i];
        std::string shaderName = shaderNames[i];
        std::string shaderFileExtension = shaderFileExtensions[i];
        ShaderCode shaderCode = getShaderCode(shaderFilePath, shaderFileExtension);
        addShaderCode(shaderCode, shaderName);
    }
}

void IOShader::addShaderCode(ShaderCode shaderCode, std::string shaderName) {
    ShaderCodeSet* shaderCodeSetPtr = nullptr;
    for (auto& shaderCodeSet : shaderCodeSets) {
        if (shaderName == shaderCodeSet.name)
            shaderCodeSetPtr = &shaderCodeSet;
    }
    if (shaderCodeSetPtr == nullptr) {
        shaderCodeSets.push_back(ShaderCodeSet{ {}, shaderName });
        shaderCodeSetPtr = &shaderCodeSets[shaderCodeSets.size() - 1];
    }
    shaderCodeSetPtr->shaders.push_back(shaderCode);
}

void IOShader::loadPrograms() {
    deletePrograms();
    for (ShaderCodeSet& shaderCodeSet : shaderCodeSets) {
        makeProgram(shaderCodeSet.shaders, shaderCodeSet.name);
    }
}

void IOShader::makeProgram(std::vector<ShaderCode> shaderCode, std::string shaderName) {
    GLuint programID = ShaderCompiler().loadShaderProgram(shaderCode);
    if (programID != 0) {
        programs[shaderName] = programID;
    }
}

void IOShader::deletePrograms() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    programs.clear();
}

GLuint IOShader::getProgram(std::string name) {
    if (!programs.contains(name)) {
        std::cout << "Error: shader program not found (" << name << ")\n";
        return 0;
    }
    return programs[name];
}

int IOShader::getNumPrograms() {
    return programs.size();
}



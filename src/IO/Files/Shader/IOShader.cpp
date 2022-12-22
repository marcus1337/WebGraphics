#include "IOShader.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>

IOShader::IOShader()
{

}

IOShader::~IOShader() {
    deletePrograms();
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
    shaderCodes.clear();
    for (int i = 0; i < shaderNames.size(); i++) {
        std::string shaderFilePath = shaderFilePaths[i];
        std::string shaderName = shaderNames[i];
        std::string shaderFileExtension = shaderFileExtensions[i];
        ShaderCode shaderCode = getShaderCode(shaderFilePath, shaderFileExtension);
        shaderCode.name = shaderName;
        shaderCodes.push_back(shaderCode);
    }
    std::cout << "Num shader code files: " << shaderCodes.size() << "\n";
    loadShaderCodeSets();
}

std::set<std::string> IOShader::getShaderCodeNames() {
    std::set<std::string> shaderNames;
    for (auto& shaderCode : shaderCodes) {
        shaderNames.insert(shaderCode.name);
    }
    return shaderNames;
}

ShaderCodeSet IOShader::getShaderCodeSet(std::string shaderName){
    ShaderCodeSet shaderCodeSet;
    shaderCodeSet.name = shaderName;
    for (ShaderCode shaderCode : shaderCodes) {
        if (shaderCode.name == shaderName) {
            shaderCodeSet.shaders.push_back(shaderCode);
        }
    }
    return shaderCodeSet;
}

void IOShader::loadShaderCodeSets() {
    shaderCodeSets.clear();
    for (std::string shaderName : getShaderCodeNames()) {
        shaderCodeSets.push_back(getShaderCodeSet(shaderName));
    }
    loadPrograms();
}

void IOShader::loadPrograms() {
    deletePrograms();
    for (ShaderCodeSet& shaderCodeSet : shaderCodeSets) {
        makeProgram(shaderCodeSet);
    }
}

void IOShader::makeProgram(ShaderCodeSet& shaderCodeSet) {
    GLuint programID = shaderCompiler.loadShaderProgram(shaderCodeSet.shaders);
    if (programID != 0)
        programs[shaderCodeSet.name] = programID;
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



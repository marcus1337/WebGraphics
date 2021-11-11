
#include "GLData.h"
#include "GLUtils.h"


GLuint GLData::makeTexture(std::string textureFile, std::string textureFilePath) {
    GLuint textID = 0;
    textID = GLUtils::load2DTexture(textureFile, textureFilePath);
    if (textID != 0)
        textures[textureFile] = textID;
    return textID;
}
GLuint GLData::makeProgram(std::vector<std::tuple<std::string, uint32_t>> shaders, std::string shaderFilePath) {
    GLuint programID = 0;
    std::string programName = getProgramName(shaders);
    programID = GLUtils::loadShaderProgram(shaders, shaderFilePath);
    if (programID != 0)
        programs[programName] = programID;
    return programID;
}

GLuint GLData::getTexture(std::string textureFile, std::string textureFilePath) {
    if (textures.contains(textureFile))
        return textures[textureFile];
    return makeTexture(textureFile, textureFilePath);
}

GLuint GLData::getProgram(std::vector<std::tuple<std::string, uint32_t>> shaders, std::string shaderFilePath) {
    std::string programName = getProgramName(shaders);
    if (programs.contains(programName))
        return programs[programName];
    return makeProgram(shaders, shaderFilePath);
}

GLData::~GLData() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    for (auto& textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
}

std::string GLData::getProgramName(std::vector<std::tuple<std::string, uint32_t>> shaders){
    std::string result;
    for(std::tuple<std::string, uint32_t> shaderInfo : shaders){
        result += std::get<0>(shaderInfo);
    }
    return result;
}

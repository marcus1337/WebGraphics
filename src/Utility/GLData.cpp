
#include "GLData.h"
#include "GLUtils.h"


GLuint GLData::makeTexture(TextureData& textureData) {
    GLuint textID = 0;
    textID = GLUtils::load2DTexture(textureData);
    if (textID != 0)
        textures[textureData.fileName] = textID;
    return textID;
}
GLuint GLData::makeProgram(std::vector<std::tuple<std::string, uint32_t>> shaders) {
    GLuint programID = 0;
    std::string programName = getProgramName(shaders);
    programID = GLUtils::loadShaderProgram(shaders);
    if (programID != 0)
        programs[programName] = programID;
    return programID;
}

GLuint GLData::getTexture(TextureData& textureData) {
    if (textures.contains(textureData.fileName))
        return textures[textureData.fileName];
    return makeTexture(textureData);
}

GLuint GLData::getProgram(std::vector<std::tuple<std::string, uint32_t>> shaders) {
    std::string programName = getProgramName(shaders);
    if (programs.contains(programName))
        return programs[programName];
    return makeProgram(shaders);
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

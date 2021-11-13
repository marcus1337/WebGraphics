
#include "GLData.h"
#include "GLUtils.h"


GLuint GLData::makeTexture(TextureData& textureData) {
    GLuint textID = 0;
    textID = GLUtils::load2DTexture(textureData);
    if (textID != 0)
        textures[textureData.fileName] = textID;
    return textID;
}
GLuint GLData::makeProgram(ShaderData& shaders) {
    GLuint programID = 0;
    programID = GLUtils::loadShaderProgram(shaders.shaders);
    if (programID != 0)
        programs[shaders.name] = programID;
    return programID;
}

GLuint GLData::getTexture(TextureData& textureData) {
    if (textures.contains(textureData.fileName))
        return textures[textureData.fileName];
    return makeTexture(textureData);
}

GLuint GLData::getProgram(ShaderData& shaders) {
    if (programs.contains(shaders.name))
        return programs[shaders.name];
    return makeProgram(shaders);
}

GLData::~GLData() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    for (auto& textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
}

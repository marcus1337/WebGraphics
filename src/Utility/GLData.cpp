
#include "GLData.h"
#include "GLUtils.h"


GLuint GLData::makeTexture(Texture texture) {
    GLuint textID = -1;

    if (texture == Texture::STALL){
        textID = GLUtils::load2DTexture("stallTexture.png", textureFilePath);
    }

    if (textID != -1)
        textures[(GLuint)texture] = textID;
    return textID;
}
GLuint GLData::makeProgram(Program program) {
    GLuint programID = -1;

    if (program == Program::MODEL){
        programID = GLUtils::loadShaderProgram("model.vert", "model.frag", shaderFilePath);
    }
    if (program == Program::IMAGE){
        programID = GLUtils::loadShaderProgram("image.vert", "image.frag", shaderFilePath);
    }

    if (programID != -1)
        programs[(GLuint)program] = programID;
    return programID;
}

void GLData::init(std::string _shaderFilePath, std::string _textureFilePath, std::string _normalTextureFilePath) {
    shaderFilePath = _shaderFilePath;
    textureFilePath = _textureFilePath;
    normalTextureFilePath = _normalTextureFilePath;
}

GLuint GLData::getTexture(GLuint texture) {
    if (textures.contains(texture))
        return textures[texture];
    return makeTexture(static_cast<GLData::Texture>(texture));
}

GLuint GLData::getProgram(GLuint program) {
    if (programs.contains(program))
        return programs[program];
    return makeProgram(static_cast<GLData::Program>(program));
}

GLData::~GLData() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    for (auto& textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
}

#include "GLData.h"
#include "GLUtils.h"


GLuint GLData::makeTexture(Texture texture) {
    GLuint textID = -1;

    if (texture == Texture::STALL){
        textID = GLUtils::load2DTexture("stallTexture.png", textureFilePath);
    }

    if (textID != -1)
        textures[texture] = textID;
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
        programs[program] = programID;
    return programID;
}

void GLData::init(std::string _shaderFilePath, std::string _textureFilePath, std::string _normalTextureFilePath) {
    shaderFilePath = _shaderFilePath;
    textureFilePath = _textureFilePath;
    normalTextureFilePath = _normalTextureFilePath;
    glGenVertexArrays(1, &vao1);
    glGenVertexArrays(1, &vao2);

}

GLuint GLData::getTexture(Texture texture) {
    if (textures.contains(texture))
        return textures[texture];
    return makeTexture(texture);
}

GLuint GLData::getProgram(Program program) {
    if (programs.contains(program))
        return programs[program];
    return makeProgram(program);
}

GLData::~GLData() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    for (auto& textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
    glDeleteVertexArrays(1, &vao1);
    glDeleteVertexArrays(1, &vao2);
}
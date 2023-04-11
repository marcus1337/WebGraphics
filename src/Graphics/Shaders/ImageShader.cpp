#include "Graphics/Shaders/ImageShader.h"
#include "IO/Files/IOContainer.h"

ImageShader::ImageShader() : Shader("image"), iotexture(IOContainer::getInstance().ioTexture) {
}

void ImageShader::setCustomUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    glUniform1f(glGetUniformLocation(programID, "grayscale"), grayscale ? 1.0f : 0.0f);
    setTextureUniforms();
}

void ImageShader::setTexture(GLuint _texture) {
    texture = _texture;
}

void ImageShader::setTexture(std::string textureName) {
    texture = iotexture.getTexture(textureName);
}

void ImageShader::setTextureUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}


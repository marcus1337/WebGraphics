#include "Graphics/Shaders/ImageShader.h"
#include "IO/Files/IOContainer.h"

ImageShader::ImageShader() : Shader("image"), defaultColor({}), normalID(0), textureID(0), iotexture(IOContainer::getInstance().ioTexture) {
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
}

void ImageShader::setCustomUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    glUniform3fv(glGetUniformLocation(programID, "defaultColor"), 1, &defaultColor[0]);
    glUniform1f(glGetUniformLocation(programID, "image"), image ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "grayscale"), grayscale ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "darken"), darken ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "fade"), fade);
    glUniform1f(glGetUniformLocation(programID, "thickness"), thickness);
    glUniform1f(glGetUniformLocation(programID, "radius"), radius);
    setClippingUniforms();
    setTextureUniforms();
}

void ImageShader::setTexture(GLuint _textureID)
{
    textureID = _textureID;
}

void ImageShader::setNormal(GLuint _textureID)
{
    normalID = _textureID;
}

void ImageShader::setTexture(std::string textureName) {
    setTexture(iotexture.getTexture(textureName));
}

void ImageShader::setNormal(std::string normalName) {
    setNormal(iotexture.getTexture(normalName));
}

void ImageShader::setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner)
{
    textureSize = _textureSize;
    textureCorner = _textureCorner;
}

void ImageShader::setClippingUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    glUniform2fv(glGetUniformLocation(programID, "inTexCoord"), 1, &textureCorner[0]);
    glUniform2fv(glGetUniformLocation(programID, "texSize"), 1, &textureSize[0]);
}

void ImageShader::setTextureUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


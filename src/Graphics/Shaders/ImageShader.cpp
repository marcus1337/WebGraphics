#include "ImageShader.h"

ImageShader::ImageShader(GLData& _glData) : Shader(_glData, "image"), defaultColor({}), normalID(0), textureID(0) {
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
}

void ImageShader::setCustomUniforms() {
    GLuint programID = glData.getProgram(programName);
    glUniform3fv(glGetUniformLocation(programID, "defaultColor"), 1, &defaultColor[0]);
    glUniform1f(glGetUniformLocation(programID, "image"), image ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "grayscale"), grayscale ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "darken"), darken ? 1.0f : 0.0f);
    glUniform2fv(glGetUniformLocation(programID, "mouse"), 1, &mouse[0]);
    glUniform1f(glGetUniformLocation(programID, "fade"), fade);
    glUniform1f(glGetUniformLocation(programID, "thickness"), thickness);
    glUniform1f(glGetUniformLocation(programID, "aspect"), scale.x/scale.y);
    glUniform1f(glGetUniformLocation(programID, "width"), scale.x);
    glUniform1f(glGetUniformLocation(programID, "height"), scale.y);
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
    setTexture(glData.getTexture(textureName));
}
void ImageShader::setNormal(std::string normalName) {
    setNormal(glData.getTexture(normalName));
}

void ImageShader::setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner)
{
    textureSize = _textureSize;
    textureCorner = _textureCorner;
}

void ImageShader::setClippingUniforms()
{
    GLuint programID = glData.getProgram(programName);
    glUniform2fv(glGetUniformLocation(programID, "inTexCoord"), 1, &textureCorner[0]);
    glUniform2fv(glGetUniformLocation(programID, "textureSize"), 1, &textureSize[0]);
}

void ImageShader::setTextureUniforms()
{
    GLuint programID = glData.getProgram(programName);
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


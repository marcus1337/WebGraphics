#include "Shader.h"


Shader::Shader(GLuint _programID) : programID(_programID), P(glm::mat4()), V(glm::mat4()), VP(glm::mat4()), normalID(0), textureID(0) {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.f, 0.f, 0.f);
    rotation = glm::angleAxis( glm::radians(0.0f), glm::vec3(0.f, 0.f, 1.f) );
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
}

Shader::~Shader(){

}

glm::mat4 Shader::getModel()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 rotateMat = glm::toMat4(rotation);
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 modModel = translateMat * rotateMat * scaleMat;
    return modModel;
}

void Shader::setUniforms(){
    glUseProgram(programID);

    setMatrixUniforms();
    setClippingUniforms();
    setColorUniforms();
    setTextureUniforms();
    setCustomUniforms();
}

void Shader::setPosition(glm::vec3 _position)
{
    position = glm::vec3(_position.x + scale.x / 2.0f, _position.y + scale.y / 2.0f, _position.z);
}

void Shader::setMidPosition(glm::vec3 _position)
{
    position = _position;
}

void Shader::setTexture(GLuint _textureID)
{
    textureID = _textureID;
}

void Shader::setNormal(GLuint _textureID)
{
   normalID = _textureID;
}

void Shader::setProgram(GLuint _programID){
    programID = _programID;
}

void Shader::setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P)
{
    VP = _VP;
    V = _V;
    P = _P;
}

void Shader::setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner)
{
    textureSize = _textureSize;
    textureCorner = _textureCorner;
}

void Shader::setColorUniforms()
{
    glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);
    glUniform1f(glGetUniformLocation(programID, "usingNormalMap"), isNormalUsed ? 1.0f : 0.0f);
}

void Shader::setClippingUniforms()
{
    glUniform2fv(glGetUniformLocation(programID, "inTexCoord"), 1, &textureCorner[0]);
    glUniform2fv(glGetUniformLocation(programID, "textureSize"), 1, &textureSize[0]);
}

void Shader::setMatrixUniforms()
{
    glm::mat4 M = getModel();
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

void Shader::setTextureUniforms()
{
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (isNormalUsed)
    {
        GLuint mTex1Handle1 = glGetUniformLocation(programID, "normalMap");
        glUniform1i(mTex1Handle1, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalID);
    }
}

void Shader::setUniform(std::string name, float value) {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
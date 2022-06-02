#include "Shader.h"

Shader::Shader(GLuint _programID) : programID(_programID), P(glm::mat4()), V(glm::mat4()), VP(glm::mat4()), normalID(0), textureID(0) {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.f, 0.f, 0.f);
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
}

Shader::~Shader(){

}

glm::mat4 Shader::getModel()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::vec3 rotationAxis(0, 0, 1.0f);
    glm::quat rotationQuat = glm::angleAxis(glm::radians(rotation), rotationAxis);
    glm::mat4 rotateMat = glm::toMat4(rotationQuat);
    glm::vec3 adjustedPosition = glm::vec3(position.x + scale.x / 2.0f, position.y + scale.y / 2.0f, position.z);
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), adjustedPosition);
    glm::mat4 modModel = translateMat * rotateMat * scaleMat;
    return modModel;
}

void Shader::setRotation(float _rotation) {
    rotation = _rotation;
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
    glUniform3fv(glGetUniformLocation(programID, "color"), 1, &color[0]);
    glUniform3fv(glGetUniformLocation(programID, "singleColor"), 1, &singleColor[0]);
    glUniform3fv(glGetUniformLocation(programID, "extraColor"), 1, &extraColor[0]);
    glUniform1f(glGetUniformLocation(programID, "isSingleColor"), isSingleColor ? 1.0f : 0.0f);
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

void Shader::setUniform(std::string name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(std::string name, glm::vec2 value) {
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

#include "Shader.h"
#include <iostream>
#include "Graphics/Camera.h"

Shader::Shader(GLuint _programID) : programID(_programID), P(glm::mat4()), V(glm::mat4()), VP(glm::mat4()), color({}), rotateOffset({}) {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.f, 0.f, 0.f);
    setViewProjectionMatrix(screenWidth, screenHeight);
}

Shader::~Shader() {

}

glm::mat4 Shader::getModel()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    if (mirror)
        scaleMat = glm::scale(glm::mat4(1.0f), { -scale.x, scale.y, scale.z });

    glm::vec3 rotationAxis(0, 0, 1.0f);
    glm::quat rotationQuat = glm::angleAxis(glm::radians(rotation), rotationAxis);
    glm::mat4 rotateMat = glm::toMat4(rotationQuat);

    glm::vec3 adjustedPosition = glm::vec3(position.x + scale.x / 2.0f, position.y + scale.y / 2.0f, position.z);
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), adjustedPosition);

    glm::mat4 offsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(-rotateOffset.x / 2.0f, -rotateOffset.y / 2.0f, 0.0f));
    glm::mat4 revertOffsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(rotateOffset.x / 2.0f, rotateOffset.y / 2.0f, 0.0f));
    glm::mat4 modModel = translateMat * revertOffsetToMiddle * rotateMat * offsetToMiddle * scaleMat;
    return modModel;
}

void Shader::setRotation(float _rotation) {
    rotation = _rotation;
}

void Shader::setUniforms() {
    glUseProgram(programID);
    setMatrixUniforms();
    setColorUniforms();
    setCustomUniforms();
}

void Shader::setPosition(glm::vec3 _position)
{
    position = _position;
}


void Shader::setProgram(GLuint _programID) {
    programID = _programID;
}

void Shader::setViewProjectionMatrix(int _width, int _height) {
    Camera camera;
    MatrixData matrixdata = camera.getMatrixData(_width, _height);
    setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
}

void Shader::setViewProjectionMatrix(glm::mat4& _VP, glm::mat4& _V, glm::mat4& _P)
{
    VP = _VP;
    V = _V;
    P = _P;
}

void Shader::setColorUniforms()
{
    glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);
    glUniform3fv(glGetUniformLocation(programID, "color"), 1, &color[0]);
}

void Shader::setMatrixUniforms()
{
    glm::mat4 M = getModel();
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

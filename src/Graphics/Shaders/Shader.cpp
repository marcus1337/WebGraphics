#include "Graphics/Shaders/Shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "IO/Files/IOContainer.h"

std::string Shader::getDefaultShaderTextureName() {
    return "tex";
}

Shader::Shader(std::string programName) : color({}), ioShader(IOContainer::getInstance().ioShader) {
    setProgram(programName);
}

Shader::~Shader() {

}

void Shader::setViewSize(int width, int height) {
    camera.setScreenSize(width, height);
}

void Shader::setModel(Model _model) {
    model = _model;
}

void Shader::setProgram(std::string _programName) {
    programName = _programName;
}

void Shader::setUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    glUseProgram(programID);
    setMatrixUniforms();
    setColorUniforms();
    setTextureUniforms();
    setCustomUniforms();
    setExtraUniforms();
}

void Shader::setTextureUniforms() {
    for (int i = 0; i < textures.size(); i++) {
        GLuint textureEnum = GL_TEXTURE0 + i;
        GLuint texture = textures[i].first;
        const char* shaderName = textures[i].second.c_str();

        GLuint program = ioShader.getProgram(programName);
        GLuint shaderTextureHandle = glGetUniformLocation(program, shaderName);
        glUniform1i(shaderTextureHandle, i);
        glActiveTexture(textureEnum);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Shader::setExtraUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    for (const auto& [key, value] : extraFloatUniforms) {
        glUniform1f(glGetUniformLocation(programID, key.c_str()), value);
    }
}

void Shader::setColorUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);
    glUniform3fv(glGetUniformLocation(programID, "color"), 1, &color[0]);
}

void Shader::setMatrixUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    glm::mat4 M = model.getModel();
    auto V = camera.getView();
    auto P = camera.getProjection();
    auto VP = P * V;
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

void Shader::setFloatUniform(std::string name, float value) {
    extraFloatUniforms[name] = value;
}

void Shader::setMatricesUniform(const std::string& name, const std::vector<glm::mat4>& arr) {
    GLuint programID = ioShader.getProgram(programName);
    GLint matrixArrayLoc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(matrixArrayLoc, arr.size(), GL_FALSE, glm::value_ptr(arr[0]));
}

void Shader::setTexture(std::string textureName, std::string shaderName) {
    GLuint texture = IOContainer::getInstance().ioTexture.getTexture(textureName);
    textures = { {texture, shaderName} };
}

void Shader::setTexture(GLuint _texture, std::string shaderName) {
    textures = { {_texture, shaderName} };
}

void Shader::setTextures(std::vector<std::pair<std::string, std::string>> _textures) {
    for (const auto& [textureName, shaderName] : _textures) {
        GLuint texture = IOContainer::getInstance().ioTexture.getTexture(textureName);
        textures.push_back({ texture , shaderName });
    }
}


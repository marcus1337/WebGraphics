#include "TextShader.h"

TextShader::TextShader(GLuint _programID) : Shader(_programID) {
    color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    setPosition(glm::vec3(0.f, 0.f, 0.f));
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = 0;
}

void TextShader::setCustomUniforms() {
    glActiveTexture(GL_TEXTURE0);
}
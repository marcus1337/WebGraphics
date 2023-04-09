#include "Graphics/Shaders/TextShader.h"

TextShader::TextShader() : Shader("text") {
    color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    model.setPosition({ 0,0,0 });
    model.setScale({ 1.0f,1.0f,1.0f });
    model.setRotation(0);
}

void TextShader::setCustomUniforms() {
    glActiveTexture(GL_TEXTURE0);
}
#include "TextShader.h"

TextShader::TextShader(IOShader& _ioShader) : Shader(_ioShader, "text") {
    color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    setPosition(0, 0);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = 0;
}

void TextShader::setCustomUniforms() {
    glActiveTexture(GL_TEXTURE0);
}
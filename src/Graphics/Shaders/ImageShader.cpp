#include "Graphics/Shaders/ImageShader.h"
#include "IO/Files/IOContainer.h"

ImageShader::ImageShader() : Shader("image"), iotexture(IOContainer::getInstance().ioTexture) {
}

void ImageShader::setCustomUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    glUniform1f(glGetUniformLocation(programID, "grayscale"), grayscale ? 1.0f : 0.0f);
}



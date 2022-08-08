
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include "IO/Files/TextureData.h"
#include "IO/Files/ShaderData.h"

#ifndef GLUTILS_H
#define GLUTILS_H

namespace GLUtils {
    void showShaderInfoLog(GLuint shader);
    void showProgramInfoLog(GLuint program);
    bool wasShaderCompiled(GLuint shader);
    GLuint linkProgram(std::vector<GLuint> shaders);
    GLuint compileShader(const ShaderCode& shaderInfo);
    std::vector<GLuint> compileShaders(std::vector<ShaderCode>& shaderInfos);
    GLuint loadShaderProgram(std::vector<ShaderCode>& shaders);
    GLuint load2DTexture(const TextureData& textureData);
}

#endif // !GLUTILS_H
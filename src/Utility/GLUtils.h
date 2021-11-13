
#ifndef GLUTILS_H
#define GLUTILS_H

#include <GL/glew.h>
#include "IO/lodepng.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

#include "GLFW/glfw3.h"

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "IO/TextureData.h"

namespace GLUtils {

    void showShaderInfoLog(GLuint shader);

    void showProgramInfoLog(GLuint program);
    bool wasShaderCompiled(GLuint shader);
    GLuint linkProgram(std::vector<GLuint> shaders);

    GLuint compileShader(const std::tuple<std::string, uint32_t>& shaderInfo);
    std::vector<GLuint> compileShaders(std::vector<std::tuple<std::string, uint32_t>> shaderInfos);
    GLuint loadShaderProgram(std::vector<std::tuple<std::string,uint32_t>> shaders);

    GLuint load2DTexture(const TextureData& textureData);


}

#endif // !GLUTILS_H

#ifndef GLUTILS_H
#define GLUTILS_H

#include <GL/glew.h>
#include "lodepng.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

#include "GLFW/glfw3.h"

#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GLUtils {

    std::string readShaderSource(const std::string& filename);

    void showShaderInfoLog(GLuint shader);

    void showProgramInfoLog(GLuint program);
    bool wasShaderCompiled(GLuint shader);
    GLuint linkProgram(std::vector<GLuint> shaders);
    GLuint compileShader(const std::string &shaderFilename, std::string &shaderFilePath, uint32_t shaderType);

    GLuint loadShaderProgram(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename, std::string& shaderFilePath);

    GLuint load2DTexture(const std::string& filename_, std::string& textureFilePath);

    GLFWimage loadIconImage(std::string& imagePath);


}

#endif // !GLUTILS_H
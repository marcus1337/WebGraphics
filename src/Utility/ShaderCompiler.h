#include <GL/glew.h>

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <map>
#include "IO/Files/ShaderData.h"
#include "IO/Files/IOShader.h"

#ifndef SHADERCOMPILER_H
#define SHADERCOMPILER_H

class ShaderCompiler {
    void printCompileError(GLuint shader);
    void printLinkError(GLuint program);
    bool wasShaderCompiled(GLuint shader);
    GLuint linkProgram(std::vector<GLuint> shaders);
    GLuint compileShader(const ShaderCode& shaderInfo);
    std::vector<GLuint> compileShaders(std::vector<ShaderCode>& shaderInfos);

public:
    GLuint loadShaderProgram(std::vector<ShaderCode>& shaders);

};

#endif // !SHADERCOMPILER_H

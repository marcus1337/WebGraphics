#include <GL/glew.h>

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <map>
#include "IO/Files/IOShader.h"
#include "IO/Files/IOTexture.h"
#include "ShaderCompiler.h"

#ifndef SHADERPROGRAMS_H
#define SHADERPROGRAMS_H

class ShaderPrograms {
    ShaderCompiler shaderCompiler;
    std::map<std::string, GLuint> programs;
    void makeProgram(ShaderCodeSet& shaderCodeSet);
    void deletePrograms();

public:
    ShaderPrograms();
    ~ShaderPrograms();
    void load(std::vector<ShaderCodeSet> shaderCodeSets);
    GLuint get(std::string name);
};

#endif // !SHADERPROGRAMS_H

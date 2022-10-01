#include <GL/glew.h>

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <map>
#include "IO/Files/TextureData.h"
#include "IO/Files/ShaderData.h"
#include "IO/Files/IOShader.h"
#include "IO/Files/IOTexture.h"
#include "ShaderCompiler.h"

#ifndef GLDATA_H
#define GLDATA_H

class GLData
{
private:
    ShaderCompiler shaderCompiler;
    std::map<std::string, GLuint> programs;
    GLuint makeProgram(ShaderData &shaders);

    IOShader ioshader;
    IOTexture iotexture;

    std::vector<ShaderData> shaders;

    GLuint getProgram(ShaderData &shaders);

public:
    GLData();
    ~GLData();
    GLuint getProgram(std::string name);
    GLuint getTexture(std::string name);
    void loadShaderCodeStrings();
};

#endif
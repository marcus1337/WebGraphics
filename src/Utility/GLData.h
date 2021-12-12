

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

#ifndef GLDATA_H
#define GLDATA_H

class GLData
{
private:
    std::map<std::string, GLuint> programs;
    std::map<std::string, GLuint> textures;
    GLuint makeTexture(TextureData &textureData);
    GLuint makeProgram(ShaderData &shaders);

    IOShader ioshader;
    std::vector<ShaderData> shaders;
    GLuint getProgram(ShaderData &shaders);

public:
    GLData();
    ~GLData();
    GLuint getTexture(TextureData &textureData);
    GLuint getProgram(std::string name);
};

#endif
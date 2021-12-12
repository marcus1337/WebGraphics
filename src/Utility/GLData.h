

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
    IOTexture iotexture;

    std::vector<ShaderData> shaders;
    std::vector<TextureData> textureInfos;

    GLuint getProgram(ShaderData &shaders);
    GLuint getTexture(TextureData &textureData);

public:
    GLData();
    ~GLData();
    GLuint getProgram(std::string name);
    GLuint getTexture(std::string name);
};

#endif
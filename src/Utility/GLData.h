

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <map>
#include "IO/TextureData.h"
#include "IO/ShaderData.h"

#ifndef GLDATA_H
#define GLDATA_H

class GLData {
public:

private:

    std::map<std::string, GLuint> programs;
    std::map<std::string, GLuint> textures;

    GLuint makeTexture(TextureData& textureData);
    GLuint makeProgram(ShaderData& shaders);

public:

    GLData() = default;
    ~GLData();
    GLuint getTexture(TextureData& textureData);
    GLuint getProgram(ShaderData& shaders);

};

#endif
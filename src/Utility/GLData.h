

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <map>

#ifndef GLDATA_H
#define GLDATA_H

class GLData {
public:

private:

    std::map<std::string, GLuint> programs;
    std::map<std::string, GLuint> textures;

    GLuint makeTexture(std::string texture, std::string textureFilePath);
    GLuint makeProgram(std::vector<std::tuple<std::string, uint32_t>> shaders, std::string shaderFilePath);
    std::string getProgramName(std::vector<std::tuple<std::string, uint32_t>> shaders);

public:

    GLData() = default;
    ~GLData();
    GLuint getTexture(std::string textureFile, std::string textureFilePath);
    GLuint getProgram(std::vector<std::tuple<std::string, uint32_t>> shaders, std::string shaderFilePath);

};

#endif
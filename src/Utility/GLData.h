

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
    enum class Program{MODEL = 0, IMAGE, TEXT};
    enum class Texture{STALL = 0};

private:

    std::map<GLuint, GLuint> programs;
    std::map<GLuint, GLuint> textures;

    GLuint makeTexture(Texture texture);
    GLuint makeProgram(Program program);

public:

    std::string shaderFilePath, textureFilePath, normalTextureFilePath;

    GLData() = default;
    void init(std::string _shaderFilePath, std::string _textureFilePath, std::string _normalTextureFilePath);

    GLuint getTexture(GLuint texture);
    GLuint getProgram(GLuint program);

    ~GLData();

};

#endif
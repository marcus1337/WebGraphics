#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"

#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

class ImageObject
{
    void initVBO();
    GLuint vao, vbo;

public:

    ImageObject();
    ~ImageObject();
    void draw(Shader& shader);
};

#endif
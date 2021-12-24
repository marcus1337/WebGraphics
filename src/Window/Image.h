#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "ImageUniform.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
    void initVBO();
    GLuint vao, vbo;

public:

    Image();
    ~Image();
    void draw(ImageUniform* imageUniform);
};

#endif
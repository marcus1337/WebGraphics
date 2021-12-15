#include <GL/glew.h>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{

    GLuint texture;

public:
    const int width, height;
    Framebuffer(int _width, int _height);

};

#endif
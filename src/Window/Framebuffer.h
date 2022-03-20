#include <GL/glew.h>
#include <functional>
#include "Shader.h"
#include "Image.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{
public:
    Shader* postImageUniform = nullptr;
    GLuint texture, fbo;
    const int width, height;
    ~Framebuffer();
    Framebuffer(int _width, int _height);
    void begin();
    void end(int windowWidth, int windowHeight);

};

#endif
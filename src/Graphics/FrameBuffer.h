#include <GL/glew.h>
#include <functional>
#include "Shader.h"
#include "ImageShader.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
public:
    ImageShader shader;
    GLuint texture, fbo;
    const int width, height;
    ~FrameBuffer();
    FrameBuffer(int _width, int _height);
    void use();

};

#endif
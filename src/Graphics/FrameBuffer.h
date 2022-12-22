#include <GL/glew.h>
#include <functional>
#include "Shaders/Shader.h"
#include "Shaders/ImageShader.h"
#include "IO/Files/IOShader.h"
#include "IO/Files/IOTexture.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
    glm::vec3 backgroundColor;
    void setBuffers();
public:
    void setTextureScaleType(unsigned int scaleType);
    ImageShader shader;
    GLuint texture, fbo;
    const int width, height;
    ~FrameBuffer();
    FrameBuffer(IOShader& _ioShader, IOTexture& _iotexture, int _width, int _height);
    void use();
    void clear(float _alpha = 1.0f);

};

#endif
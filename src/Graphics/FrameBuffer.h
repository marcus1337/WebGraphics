#include <GL/glew.h>
#include <functional>
#include "Shaders/Shader.h"
#include "Shaders/ImageShader.h"
#include <Utility/GLData.h>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class FrameBuffer
{
    glm::vec3 backgroundColor;
public:
    ImageShader shader;
    GLuint texture, fbo;
    const int width, height;
    ~FrameBuffer();
    FrameBuffer(GLData& gldata, int _width, int _height);
    void use();
    void clear();

};

#endif
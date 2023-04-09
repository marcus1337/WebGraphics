
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <GL/glew.h>
#include <functional>
#include "Shaders/Shader.h"
#include "Shaders/ImageShader.h"
#include "IO/Files/Shader/IOShader.h"
#include "IO/Files/Texture/IOTexture.h"
#include <array>

class FrameBuffer
{
    glm::vec3 backgroundColor;
    void setBuffers();

    GLuint oldFBO;
    std::array<GLint, 4> oldViewport;

public:
    void storeState();
    void loadState();

    void setTextureScaleType(unsigned int scaleType);
    ImageShader shader;
    GLuint texture, fbo;
    const int width, height;
    ~FrameBuffer();
    FrameBuffer(int _width, int _height);
    void use();
    void clear(float _alpha = 1.0f);
    void useViewPort();

};

#endif
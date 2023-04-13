
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
    GLuint oldFBO;
    std::array<GLint, 4> oldViewport;
    GLuint depthBuffer = 0;
    GLuint texture = 0;
    GLuint fbo = 0;
    void setBuffers();
    void setFBO();
    void setDepthBuffer();

public:
    const int width, height;
    ImageShader shader;

    void storeState();
    void loadState();

    void setTextureScaleType(unsigned int scaleType);
    ~FrameBuffer();
    FrameBuffer(int _width, int _height);
    void use();
    void clear(float _alpha = 1.0f);
    void useViewPort();

};

#endif
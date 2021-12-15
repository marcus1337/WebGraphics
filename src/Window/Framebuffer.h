#include <GL/glew.h>
#include <functional>
#include "ImageUniform.h"

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class Framebuffer
{

    GLuint texture, fbo;
    void begin();
    void end(int windowWidth, int windowHeight);
    void drawFramebuffer();

public:
    const int width, height;
    Framebuffer(int _width, int _height);
    void draw(std::function<void(void)>& drawFunc, int windowWidth, int windowHeight);

};

#endif
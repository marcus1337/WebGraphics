#include "Framebuffer.h"

Framebuffer::Framebuffer(int _width, int _height) : width(_width), height(_height)
{
}

void Framebuffer::draw(std::function<void(void)> &drawFunc, int windowWidth, int windowHeight)
{
    begin();
    drawFunc();
    end(windowWidth, windowHeight);
    drawFramebuffer();
}

void Framebuffer::begin()
{
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}
void Framebuffer::end(int windowWidth, int windowHeight)
{
    glViewport(0, 0, windowWidth, windowHeight);
}

 void Framebuffer::drawFramebuffer(){

 }
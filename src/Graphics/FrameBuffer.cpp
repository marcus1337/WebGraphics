#include "Graphics/FrameBuffer.h"
#include <iostream>
#include "Engine/Engine.h"
#include "Graphics/Shaders/Model.h"

FrameBuffer::FrameBuffer(int _width, int _height) : width(_width), height(_height)
{
    setBuffers();
    shader.setTexture(texture);
    backgroundColor = glm::vec3(0.2f, 0.2f, 0.2f);
}

void FrameBuffer::setTextureScaleType(unsigned int scaleType) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaleType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, scaleType);
}

void FrameBuffer::setBuffers() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    setTextureScaleType(GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}

void FrameBuffer::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

void FrameBuffer::clear(float _alpha) {
    use();
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, _alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void FrameBuffer::storeState() {
    glGetIntegerv(GL_VIEWPORT, oldViewport.data());
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&oldFBO);
}

void FrameBuffer::loadState() {
    glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
    glViewport(oldViewport[0], oldViewport[1], oldViewport[2], oldViewport[3]);
}
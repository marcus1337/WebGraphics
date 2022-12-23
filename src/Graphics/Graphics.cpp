#include "Graphics.h"
#include <algorithm>
#include <iostream>

Graphics::Graphics(Canvas& _window, IOShader& _ioShader, IOTexture& _ioTexture, IOFonts& _ioFonts) : window(_window), mainView(_window, imageObject, _ioShader, _ioTexture), ioTexture(_ioTexture), ioFonts(_ioFonts), textObject(_ioFonts), ioShader(_ioShader)
{
    setGLSettings();
}

void Graphics::setGLSettings() {
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.0f, 1.0f);
}


Graphics::~Graphics() {
}


#include "Graphics.h"
#include <algorithm>
#include <iostream>

Graphics::Graphics(Canvas& _window) : window(_window), mainView(glData, 1920, 1080)
{
    outerBackgroundColor = glm::vec3(0.05f, 0.05f, 0.05f);
    window.appResizeCallbackFunction = std::bind(&Graphics::display, this);
}


Graphics::~Graphics() {
}

void Graphics::useMainView() {
    mainView.use();
}

void Graphics::clearView() {
    mainView.clear();
}

void Graphics::display() {
    drawMainView();
    window.display();
}

int Graphics::getScreenWidth() {
    return mainView.width;
}
int Graphics::getScrenHeight() {
    return mainView.height;
}

void Graphics::drawMainView() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(outerBackgroundColor.r, outerBackgroundColor.g, outerBackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    window.aspectRatio.setIndexToLessOrEqual(window.width, window.height);
    int frameWidth = window.aspectRatio.getWidth();
    int frameHeight = window.aspectRatio.getHeight();
    float frameXPos = (float)(window.width - frameWidth) / 2.0f;
    float frameYPos = (float)(window.height - frameHeight) / 2.0f;

    mainView.shader.setPosition(glm::vec3(frameXPos, frameYPos, 0.f));
    mainView.shader.scale = glm::vec3((float)frameWidth, (float)frameHeight, 1.0f);
    glViewport(0, 0, window.width, window.height);
    mainView.shader.setViewProjectionMatrix(window.width, window.height);
    imageObject.draw(mainView.shader);
}




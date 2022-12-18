#include "Graphics.h"
#include <algorithm>
#include <iostream>

Graphics::Graphics(Canvas& _window) : window(_window), mainView(shaderPrograms, iotexture, 1920, 1080)
{
    setGLSettings();
    outerBackgroundColor = glm::vec3(0.05f, 0.05f, 0.05f);
    window.setResizeCallbackFunction(std::bind(&Graphics::display, this));
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

int Graphics::getMainViewWidth() { //Aspect ratio 16:9
    const int maxViewWidth = 1920;
    const int maxViewHeight = 1080;
    const int minValue = 50;//Arbitrary value >0 to prevent drawing graphics to a zero-sized canvas.
    int windowWidth = window.getWidth();
    int windowHeight = window.getHeight();

    if (windowWidth >= maxViewWidth && windowHeight >= maxViewHeight)
        return maxViewWidth;
    if (windowWidth < minValue || windowHeight < minValue)
        return minValue; 

    if ( (int)((windowWidth / 16.0f) * 9.0f) <= windowHeight)
        return windowWidth;

    return (int) ((windowHeight / 9.0f) * 16.0f);
}

int Graphics::getMainViewHeight() { //Aspect ratio 16:9
    return (int)((getMainViewWidth() / 16.0f) * 9.0f);
}

void Graphics::drawMainView() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(outerBackgroundColor.r, outerBackgroundColor.g, outerBackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    int frameWidth = getMainViewWidth();
    int frameHeight = getMainViewHeight();
    float frameXPos = (float)(window.getWidth() - frameWidth) / 2.0f;
    float frameYPos = (float)(window.getHeight() - frameHeight) / 2.0f;

    mainView.shader.setPosition(frameXPos, frameYPos);
    mainView.shader.setScale(frameWidth, frameHeight);
    glViewport(0, 0, window.getWidth(), window.getHeight());
    mainView.shader.setViewProjectionMatrix(window.getWidth(), window.getHeight());
    imageObject.draw(mainView.shader);
}

std::pair<int, int> Graphics::getPixelPosition(int _x, int _y) {
    _x -= mainView.shader.getX();
    _y -= mainView.shader.getY();
    _x = std::clamp(_x, 0, mainView.shader.getWidth());
    _y = std::clamp(_y, 0, mainView.shader.getHeight());
    float relX = (float)_x / mainView.shader.getWidth();
    float relY = (float)_y / mainView.shader.getHeight();
    return std::make_pair((int)(relX * mainView.width), (int)(relY * mainView.height));
}

std::pair<int, int> Graphics::getMousePixelPosition() {
    return getPixelPosition(window.mouse.x, window.mouse.y);
}

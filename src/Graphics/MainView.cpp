#include "Graphics/MainView.h"
#include <algorithm>
#include <functional>

MainView::MainView(Canvas& _window, ImageObject& _imageObject, IOShader& _ioShader, IOTexture& _iotexture) : imageObject(_imageObject), view(_ioShader, _iotexture, maxWidth, maxHeight), window(_window)
{
    outerBackgroundColor = glm::vec3(0.05f, 0.05f, 0.05f);
    window.setResizeCallbackFunction(std::bind(&MainView::display, this));
}

int MainView::getX() {
    return (int)((window.getWidth() - getWidth()) / 2.0f);
}

int MainView::getY() {
    return (int)((window.getHeight() - getHeight()) / 2.0f);
}

int MainView::getWidth() {
    const int minValue = 50;//Arbitrary value >0 to prevent drawing graphics to a zero-sized canvas.
    int windowWidth = window.getWidth();
    int windowHeight = window.getHeight();

    if (windowWidth >= maxWidth && windowHeight >= maxHeight)
        return maxWidth;
    if (windowWidth < minValue || windowHeight < minValue)
        return minValue;

    if ((int)((windowWidth / 16.0f) * 9.0f) <= windowHeight)
        return windowWidth;

    return (int)((windowHeight / 9.0f) * 16.0f);
}

int MainView::getHeight() {
    return (int)((getWidth() / 16.0f) * 9.0f);
}

void MainView::use() {
    view.use();
}

void MainView::clear() {
    view.clear();
}

void MainView::display() {
    render();
    window.display();
}

std::pair<int, int> MainView::getPixelPosition(int _x, int _y) {
    _x -= getX();
    _y -= getY();
    _x = std::clamp(_x, 0, getWidth());
    _y = std::clamp(_y, 0, getHeight());
    float relX = (float)_x / getWidth();
    float relY = (float)_y / getHeight();
    return std::make_pair((int)(relX * maxWidth), (int)(relY * maxHeight));
}

std::pair<int, int> MainView::getMousePosition() {
    return getPixelPosition(window.mouse.x, window.mouse.y);
}

void MainView::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    view.shader.setPosition(getX(), getY());
    view.shader.setScale(getWidth(), getHeight());
    glViewport(0, 0, window.getWidth(), window.getHeight());
    view.shader.setViewProjectionMatrix(window.getWidth(), window.getHeight());
    imageObject.draw(view.shader);
}


#include "Graphics/MainView.h"
#include <algorithm>
#include <functional>
#include "Graphics/Objects/ObjectContainer.h"
#include "Graphics/Shaders/Camera.h"
#include "Graphics/Shaders/Model.h"
#include <numeric>

MainView::MainView(Canvas& _window) : window(_window)
{
    setSize(1920, 1080);
    outerBackgroundColor = glm::vec3(0.05f, 0.05f, 0.05f);
    window.setResizeCallbackFunction(std::bind(&MainView::display, this));
}

int MainView::getX() {
    return (int)((window.getWidth() - getWidth()) / 2.0f);
}

int MainView::getY() {
    return (int)((window.getHeight() - getHeight()) / 2.0f);
}

std::pair<int, int> MainView::getAspectRatio() {
    int gcd = std::gcd(frame->width, frame->height);
    int widthRatio = frame->width / gcd;
    int heightRatio = frame->height / gcd;
    int aspectRatioGCD = std::gcd(widthRatio, heightRatio);
    widthRatio /= aspectRatioGCD;
    heightRatio /= aspectRatioGCD;
    return {widthRatio, heightRatio };
}

std::pair<int, int> MainView::getFrameDimension() {
    auto aspectRatio = getAspectRatio();
    float widthRatio = static_cast<float>(aspectRatio.first);
    float heightRatio = static_cast<float>(aspectRatio.second);

    int adjustedWidth = (int)((window.getHeight() / heightRatio) * widthRatio);
    int adjustedHeight = (int)((window.getWidth() / widthRatio) * heightRatio);
    int width = adjustedHeight <= window.getHeight() ? window.getWidth() : adjustedWidth;
    int height = adjustedWidth <= window.getWidth() ? window.getHeight() : adjustedHeight;
    
    return { width, height };
}

bool MainView::isWindowMinimized() {
    return window.getWidth() < minFrameSize || window.getHeight() < minFrameSize;
}

int MainView::getWidth() {
    if (isWindowMinimized())
        return minFrameSize;
    return getFrameDimension().first;
}

int MainView::getHeight() {
    if (isWindowMinimized())
        return minFrameSize;
    return getFrameDimension().second;
}

void MainView::setSize(int width, int height) {
    frame = std::shared_ptr<FrameBuffer>(new FrameBuffer(width, height));
}

void MainView::clear() {
    frame->clear();
}

void MainView::use() {
    frame->use();
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
    return std::make_pair((int)(relX * frame->width), (int)(relY * frame->height));
}

std::pair<int, int> MainView::getMousePosition() {
    return getPixelPosition(window.mouse.getX(), window.mouse.getY());
}

void MainView::useDefaultFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window.getWidth(), window.getHeight());
}

void MainView::setFrameModel() {
    Model model;
    model.setPosition({ getX(), getY(), -5 });
    model.setScale({ getWidth(), getHeight(), 1.0f });
    frame->shader.setModel(model);
}

void MainView::render() {
    useDefaultFramebuffer();
    setFrameModel();
    frame->shader.setViewSize(window.getWidth(), window.getHeight());
    ObjectContainer::getInstance().imageObj.draw(frame->shader);
}

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

int MainView::getWidth() {
    if (window.getWidth() >= frame->width && window.getHeight() >= frame->height)
        return frame->width;
    const int minSize = 50;
    if (window.getWidth() < minSize || window.getHeight() < minSize)
        return minSize;

    auto aspectRatio = getAspectRatio();
    float widthRatio = (float) aspectRatio.first;
    float heightRatio = (float) aspectRatio.second;

    if ((int)((window.getWidth() / widthRatio) * heightRatio) <= window.getHeight())
        return window.getWidth();
    else
        return (int)((window.getHeight() / heightRatio) * widthRatio);
}

int MainView::getHeight() {
    if (window.getWidth() >= frame->width && window.getHeight() >= frame->height)
        return frame->height;
    const int minSize = 50;
    if (window.getWidth() < minSize || window.getHeight() < minSize)
        return minSize;

    auto aspectRatio = getAspectRatio();
    float widthRatio = (float)aspectRatio.first;
    float heightRatio = (float)aspectRatio.second;

    if ((int)((window.getWidth() / widthRatio) * heightRatio) <= window.getHeight())
        return (int)((window.getWidth() / widthRatio) * heightRatio);
    else
        return window.getHeight();
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
    return getPixelPosition(window.mouse.x, window.mouse.y);
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

void MainView::setFrameCamera() {
    auto windowCamera = frame->shader.getCamera();
    windowCamera->setScreenSize(window.getWidth(), window.getHeight());
}

void MainView::render() {
    useDefaultFramebuffer();
    setFrameModel();
    setFrameCamera();
    ObjectContainer::getInstance().imageObj.draw(frame->shader);
}

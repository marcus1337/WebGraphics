#include "View.h"
#include "Rect.h"

View::View(Graphics& _graphics, IOContainer& _ioContainer, int _pixelWidth, int _pixelHeight) : Drawable(_graphics, _ioContainer, frameBuffer.shader),
frameBuffer(_ioContainer.ioShader, _ioContainer.ioTexture, _pixelWidth, _pixelHeight), pixelWidth(_pixelWidth), pixelHeight(_pixelHeight) {
}

View::~View() {
}

void View::clear() {
    frameBuffer.clear(0.0f);
}

void View::paint(Drawable& drawable) {
    frameBuffer.use();
    drawable.setViewProjectionMatrix(pixelWidth, pixelHeight);
    drawable.render();
    graphics.mainView.use();
    drawable.setViewProjectionMatrix(graphics.mainView.getWidth(), graphics.mainView.getHeight());
}

void View::paintMinusAlpha(Drawable& drawable) {
    int blendFuncValues[2];
    glGetIntegerv(GL_BLEND_SRC, &blendFuncValues[0]);
    glGetIntegerv(GL_BLEND_DST, &blendFuncValues[1]);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    paint(drawable);

    glBlendFunc(blendFuncValues[0], blendFuncValues[1]);
}

void View::subPaint(Drawable& drawable) {
    int blendFuncValues[2];
    glGetIntegerv(GL_BLEND_SRC, &blendFuncValues[0]);
    glGetIntegerv(GL_BLEND_DST, &blendFuncValues[1]);

    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    paint(drawable);

    glBlendFunc(blendFuncValues[0], blendFuncValues[1]);
}

void View::render() {
    graphics.imageObject.draw(frameBuffer.shader);
}

void View::setPixelColor(int _x, int _y, glm::vec3 _color) {
    glm::vec4 _pixel = getPixel(_x, _y);
    setPixel(_x, _y, glm::vec4(_color, _pixel.a));
}

void View::setPixelAlpha(int _x, int _y, float _alpha) {
    glm::vec4 _pixel = getPixel(_x, _y);
    setPixel(_x, _y, glm::vec4(glm::vec3(_pixel), _alpha));
}

void View::setPixel(int _x, int _y, glm::vec4 _color) {
    frameBuffer.use();
    glEnable(GL_SCISSOR_TEST);
    glScissor(_x, _y, 1, 1);
    glClearColor(_color.x, _color.y, _color.z, _color.a);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    graphics.mainView.use();
}

glm::vec4 View::getPixel(int _x, int _y) {
    frameBuffer.use();
    glm::vec4 _color;
    glReadPixels(_x, _y, 1, 1, GL_RGBA, GL_FLOAT, &_color);
    graphics.mainView.use();
    return _color;
}

void View::setRenderPixelPerfect() {
    frameBuffer.setTextureScaleType(GL_NEAREST);
}

int View::getPixelWidth() {
    return pixelWidth;
}

int View::getPixelHeight() {
    return pixelHeight;
}

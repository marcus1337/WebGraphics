#include "Drawables/View.h"
#include "Drawables/Rect.h"

View::View(int _pixelWidth, int _pixelHeight, bool depthBuffer) : Drawable(frameBuffer.shader),
frameBuffer(_pixelWidth, _pixelHeight, depthBuffer), pixelWidth(_pixelWidth), pixelHeight(_pixelHeight) {
    model.setScale({ (float)_pixelWidth, (float)_pixelHeight, 1.0f });

}

View::~View() {
}

void View::clear() {
    frameBuffer.storeState();
    frameBuffer.clear(0.0f);
    frameBuffer.loadState();
}

void View::paint(Drawable& drawable) {
    frameBuffer.storeState();
    frameBuffer.use();
    drawable.render();
    frameBuffer.loadState();
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
    frameBuffer.storeState();
    frameBuffer.shader.setModel(model);
    objectContainer.imageObj.draw(frameBuffer.shader);
    frameBuffer.loadState();
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

void View::setPixel(int x, int y, glm::vec3 color) {
    frameBuffer.setPixel(x, y, color);
}


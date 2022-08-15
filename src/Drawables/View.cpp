#include "View.h"

View::View(Engine& _engine, int _pixelWidth, int _pixelHeight) : Drawable(_engine, frameBuffer.shader),
    frameBuffer(engine.graphics.glData, _pixelWidth, _pixelHeight), pixelWidth(_pixelWidth), pixelHeight(_pixelHeight) {
}

View::~View() {
}

void View::clear() {
    frameBuffer.clear();
}

void View::paint(Drawable& drawable) {
    frameBuffer.use();
    drawable.setViewProjectionMatrix(pixelWidth, pixelHeight);
    drawable.render();
    engine.graphics.useMainView();
    drawable.setViewProjectionMatrix(graphics.getScreenWidth(), graphics.getScrenHeight());
}

void View::render() {
    graphics.imageObject.draw(frameBuffer.shader);
}


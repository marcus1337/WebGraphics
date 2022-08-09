#include "View.h"

View::View(Engine& _engine, int _pixelWidth, int _pixelHeight) : Drawable(_engine),
    frameBuffer(engine.graphics.glData, _pixelWidth, _pixelHeight), pixelWidth(_pixelWidth), pixelHeight(_pixelHeight) {
    shader = &frameBuffer.shader;
}

View::~View() {
    shader = nullptr;
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
    graphics.imageObject.draw(*shader);
}



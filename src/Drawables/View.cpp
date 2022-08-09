#include "View.h"

View::View(Engine& _engine, int _pixelWidth, int _pixelHeight) : Drawable(_engine), frameBuffer(engine.graphics.glData, _pixelWidth, _pixelHeight) {
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
    drawable.render();
    engine.graphics.useMainView();
}

void View::render() {
    graphics.imageObject.draw(*shader);
}
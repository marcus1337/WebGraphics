#include "Rect.h"

Rect::Rect(Engine& _engine) : Drawable(_engine) {
    shader = new ImageShader(graphics.glData.getProgram("rectangle"));
}

void Rect::render() {
    graphics.imageObject.draw(*shader);
}
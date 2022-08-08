#include "Rect.h"

Rect::Rect(Engine& _engine) : Drawable(_engine) {
    shader->setProgram(graphics.glData.getProgram("rectangle"));
}

void Rect::render() {
    graphics.imageObject.draw(*shader);
}
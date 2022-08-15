#include "Rect.h"

Rect::Rect(Engine& _engine) : Drawable(_engine, imageShader), imageShader(_engine.graphics.glData) {
    imageShader.setProgram("rectangle");
}

void Rect::render() {
    graphics.imageObject.draw(imageShader);
}
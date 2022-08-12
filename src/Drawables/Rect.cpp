#include "Rect.h"

Rect::Rect(Engine& _engine) : Drawable(_engine, imageShader) {
    imageShader.setProgram(graphics.glData.getProgram("rectangle"));
}

void Rect::render() {
    graphics.imageObject.draw(imageShader);
}
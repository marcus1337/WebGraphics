#include "Rect.h"

Rect::Rect(Engine& _engine) : Drawable(_engine, imageShader), imageShader(_engine.graphics.shaderPrograms, _engine.graphics.iotexture) {
    imageShader.setProgram("rectangle");
    setThickness(1.0f);
}

void Rect::render() {
    graphics.imageObject.draw(imageShader);
}

void Rect::setFade(float _fade) {
    imageShader.fade = _fade;
}

void Rect::setThickness(float _thickness) {
    imageShader.thickness = _thickness;
}

void Rect::setRadius(float _radius) {
    imageShader.radius = _radius;
}


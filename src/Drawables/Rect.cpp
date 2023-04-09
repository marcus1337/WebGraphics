#include "Drawables/Rect.h"

Rect::Rect() : Drawable(imageShader) {
    imageShader.setProgram("rectangle");
    setThickness(1.0f);
    setRadius(0.0f);
}

void Rect::render() {
    imageShader.setModel(model);
    objectContainer.imageObj.draw(imageShader);
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


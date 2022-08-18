
#include "Circle.h"

Circle::Circle(Engine& _engine) : Drawable(_engine, imageShader), imageShader(_engine.graphics.glData) {
    imageShader.setProgram("circle");
}

void Circle::render() {
    graphics.imageObject.draw(imageShader);
}

void Circle::setFade(float _fade) {
    imageShader.fade = _fade;
}

void Circle::setThickness(float _thickness) {
    imageShader.thickness = _thickness;
}
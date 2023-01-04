#include "Rect.h"

Rect::Rect(Graphics& _graphics, IOContainer& _ioContainer) : Drawable(_graphics, _ioContainer, imageShader), imageShader(_ioContainer.ioShader, _ioContainer.ioTexture) {
    imageShader.setProgram("rectangle");
    setThickness(1.0f);
    setRadius(0.0f);
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


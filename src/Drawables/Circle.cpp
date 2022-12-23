
#include "Circle.h"

Circle::Circle(Graphics& _graphics, IOContainer& _ioContainer) : Drawable(_graphics, _ioContainer, imageShader), imageShader(_ioContainer.ioShader, _ioContainer.ioTexture) {
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
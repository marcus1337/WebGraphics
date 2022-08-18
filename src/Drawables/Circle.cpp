
#include "Circle.h"

Circle::Circle(Engine& _engine) : Drawable(_engine, imageShader), imageShader(_engine.graphics.glData) {
    imageShader.setProgram("circle");
}

void Circle::render() {
    graphics.imageObject.draw(imageShader);
}

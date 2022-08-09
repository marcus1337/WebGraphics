#include "Image.h"

Image::Image(Engine& _engine) : Drawable(_engine) {
    shader = new ImageShader(graphics.glData.getProgram("image"));
    shader->rotation = 180.0f;
    ((ImageShader*)shader)->setTexture(graphics.glData.getTexture("background1.png"));
    ((ImageShader*)shader)->mirror = true;
}

void Image::render() {
    graphics.imageObject.draw(*shader);
}

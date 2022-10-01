#include "Image.h"

Image::Image(Engine& _engine, std::string _texture) : Drawable(_engine, imageShader), imageShader(_engine.graphics.shaderPrograms, _engine.graphics.iotexture) {
    imageShader.rotation = 180.0f;
    imageShader.setTexture(_texture);
    imageShader.mirror = true;
}

void Image::render() {
    graphics.imageObject.draw(imageShader);
}

void Image::setTexture(std::string textureName) {
    imageShader.setTexture(textureName);
}


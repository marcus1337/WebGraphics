#include "Image.h"

Image::Image(Graphics& _graphics, IOContainer& _ioContainer, std::string _texture) : Drawable(_graphics, _ioContainer, imageShader), imageShader(_ioContainer.ioShader, _ioContainer.ioTexture) {
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


#include "Drawables/Image.h"

Image::Image(std::string _texture) : Drawable(imageShader) {
    imageShader.rotation = 180.0f;
    imageShader.setTexture(_texture);
    imageShader.mirror = true;
}

void Image::render() {
    objectContainer.imageObj.draw(imageShader);
}

void Image::setTexture(std::string textureName) {
    imageShader.setTexture(textureName);
}


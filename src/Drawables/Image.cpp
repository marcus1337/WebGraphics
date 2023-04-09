#include "Drawables/Image.h"

Image::Image(std::string _texture) : Drawable(imageShader) {
    setRotation(180.0f);
    imageShader.setTexture(_texture);
    model.setMirror(true);
}

void Image::render() {
    imageShader.setModel(model);
    objectContainer.imageObj.draw(imageShader);
}

void Image::setTexture(std::string textureName) {
    imageShader.setTexture(textureName);
}


#include "Drawables/Image.h"

Image::Image(std::string _texture) : Drawable(imageShader) {
    setRotation({0.f,0.f, 180.0f });
    imageShader.setTexture(_texture, "tex");
}

void Image::render() {
    imageShader.setModel(model);
    objectContainer.imageObj.draw(imageShader);
}

void Image::setTexture(std::string textureName) {
    imageShader.setTexture(textureName, "tex");
}


#include "Image.h"

Image::Image(Engine& _engine) : Drawable(_engine) {
    shader = new ImageShader(graphics.glData.getProgram("image"));
    shader->rotation = 180.0f;
    setTexture("background1.png");
    setMirror(true);
}

void Image::setTexture(std::string _texture) {
    ((ImageShader*)shader)->setTexture(graphics.glData.getTexture(_texture));
}
void Image::setSingleColor(glm::vec3 _color) {
    ((ImageShader*)shader)->singleColor = _color;
}
void Image::setMirror(bool _mirror) {
    ((ImageShader*)shader)->mirror = _mirror;
}
void Image::setEffect(float _effect) {
    ((ImageShader*)shader)->effect = _effect;
}
void Image::setIsSingleColor(bool _isSingleColor) {
    ((ImageShader*)shader)->isSingleColor = _isSingleColor;
}
void Image::setGray(bool _gray) {
    ((ImageShader*)shader)->grayscale = _gray;
}
void Image::setDark(bool _dark) {
    ((ImageShader*)shader)->darken = _dark;
}

void Image::render() {
    graphics.imageObject.draw(*shader);
}

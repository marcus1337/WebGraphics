#include "Text.h"
#include "Graphics/Shaders/TextShader.h"

Text::Text(Engine& _engine) : Drawable(_engine, textShader), textShader(_engine.graphics.shaderPrograms) {

}

void Text::render() {
    graphics.textObject.setFont(font);
    graphics.textObject.setText(text);
    graphics.textObject.setTextPixelHeight(pixelHeight);
    graphics.textObject.draw(textShader);
}

unsigned int Text::getPixelWidth() {
    graphics.textObject.setFont(font);
    return graphics.textObject.getTextWidth(text, pixelHeight, font);
}

void Text::setText(std::string _text) {
    text = _text;
}
void Text::setFont(std::string _font) {
    font = _font;
}
void Text::setPixelHeight(unsigned int _pixelHeight) {
    pixelHeight = _pixelHeight;
}

unsigned int Text::getPixelHeight() {
    return pixelHeight;
}

void Text::center(int _x, int _y, int _width, int _height) {
    int textWidth = getPixelWidth();
    int textHeight = getPixelHeight();
    int xOffset = (_width - textWidth) / 2;
    int yOffset = (_height - textHeight) / 2;
    setPosition(_x + xOffset, _y + yOffset);
}
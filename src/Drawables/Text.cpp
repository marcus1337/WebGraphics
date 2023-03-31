#include "Drawables/Text.h"
#include "Graphics/Shaders/TextShader.h"

Text::Text() : Drawable(textShader) {

}

void Text::render() {
    objectContainer.textObj.setFont(font);
    objectContainer.textObj.setText(text);
    objectContainer.textObj.setTextPixelHeight(pixelHeight);
    objectContainer.textObj.draw(textShader);
}

unsigned int Text::getPixelWidth() {
    objectContainer.textObj.setFont(font);
    return objectContainer.textObj.getTextWidth(text, pixelHeight, font);
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
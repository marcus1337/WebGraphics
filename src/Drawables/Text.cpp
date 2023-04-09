#include "Drawables/Text.h"
#include "Graphics/Shaders/TextShader.h"

Text::Text() : Drawable(textShader) {

}

void Text::render() {
    auto& textObj = objectContainer.textObj;
    auto textWidth = glm::vec2(textObj.getTextWidth(text, pixelHeight, font), pixelHeight);
    model.setRotateOffset(textWidth);
    textObj.setFont(font);
    textObj.setText(text);
    textObj.setTextPixelHeight(pixelHeight);
    textShader.setModel(model);
    textObj.draw(textShader);
}

unsigned int Text::getPixelWidth() {
    objectContainer.textObj.setFont(font);
    return objectContainer.textObj.getTextWidth(text, pixelHeight, font);
}

void Text::setText(std::wstring _text) {
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
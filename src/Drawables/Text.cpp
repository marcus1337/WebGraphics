#include "Text.h"
#include "Graphics/Shaders/TextShader.h"

Text::Text(Engine& _engine) : Drawable(_engine) {
    shader = new TextShader(graphics.glData.getProgram("text"));
}

void Text::render() {
    graphics.textObject.setFont(font);
    graphics.textObject.setText(text);
    graphics.textObject.setTextPixelHeight(pixelHeight);
    graphics.textObject.draw(*shader);
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

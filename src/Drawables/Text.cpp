#include "Text.h"

Text::Text(std::string _text, std::string _font, unsigned int _pixelHeight) : text(_text),
font(_font), pixelHeight(_pixelHeight) {

}


void Text::render(Graphics& _graphics) {
    TextShader& _shader = _graphics.textShader;
    _graphics.textObject.setFont(font);
    _graphics.textObject.setText(text);
    _graphics.textObject.setTextPixelHeight(pixelHeight);
    _shader.setPosition(glm::vec3(x, y, 0.0f));
    _shader.rotation = rotation;
    _shader.color = glm::vec3(color.r, color.g, color.b);
    _shader.alpha = color[3];
    _graphics.textObject.draw(_shader);
}

unsigned int Text::getPixelWidth(Graphics& _graphics) {
    _graphics.textObject.setFont(font);
    return _graphics.textObject.getTextWidth(text, pixelHeight, font);
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
void Text::setColor(glm::vec3 _color) {
    color = glm::vec4(_color, color[3]);
}
void Text::setColor(glm::vec4 _color) {
    color = _color;
}
void Text::setAlpha(float _alpha) {
    color[3] = _alpha;
}
unsigned int Text::getPixelHeight() {
    return pixelHeight;
}

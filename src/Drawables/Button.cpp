#include "Button.h"
#include <iostream>
#include "ButtonImage.h"

Button::Button(ButtonType _buttonType)
{
    text = Text("", "Roboto-Regular", 30);
    text.setColor({ 0.8f, 0.8f, 1.0f });
    image = makeImage(_buttonType);
    image->texture = "button1.png";
    image->width = 300;
}

Image* Button::makeImage(ButtonType _buttonType) {
    if (_buttonType == ButtonType::PLAIN)
        return new ButtonImage();
    else if (_buttonType == ButtonType::SETTING)
        return new Image();
    return nullptr;
}

Button::Button(const Button& _button) {
    *this = _button;
}

Button& Button::operator=(const Button& _btn) {
    if (this == &_btn)
        return *this;
    if (image != nullptr)
        delete image;
    image = nullptr;
    if (_btn.image != nullptr)
        this->image = _btn.image->clone();
    this->active = _btn.active;
    this->defaultColor = _btn.defaultColor;
    this->highlightColor = _btn.highlightColor;
    this->highlighted = _btn.highlighted;
    this->holdPress = _btn.holdPress;
    this->shaderTimer = _btn.shaderTimer;
    this->text = _btn.text;
    this->viewIndex = _btn.viewIndex;
    this->onPressCallback = _btn.onPressCallback;
    return *this;
}

Button::~Button() {
    delete image;
}

void Button::onPress(int _x, int _y)
{
    if (isPointerInside(_x, _y))
    {
        pressed = true;
        image->extraColor = getPressedColor();
    }
    else
    {
        pressed = false;
        image->extraColor = defaultColor;
    }
}
void Button::onRelease(int _x, int _y)
{
    if (pressed && isPointerInside(_x, _y) && onPressCallback)
    {
        onPressCallback();
    }
    image->extraColor = defaultColor;
    pressed = false;
    onHover(_x, _y);
}

void Button::onHover(int _x, int _y)
{
    if (isPointerInside(_x, _y))
    {
        if (!highlighted)
            onHoverEnter(_x, _y);
        highlighted = true;
        if (!pressed) {
            image->extraColor = getHighlightColor();
        }
    }
    else
    {
        if (highlighted)
            onHoverExit(_x, _y);
        highlighted = false;
        if (!pressed) {
            image->extraColor = defaultColor;
        }
    }
    image->isHighlighted = highlighted;
    image->mouseX = getMouseXInterval(_x);
    image->mouseY = getMouseYInterval(_y);
}

void Button::onHoverEnter(int _x, int _y) {
    image->mouseX = getMouseXInterval(_x);
    image->mouseY = getMouseYInterval(_y);
}

void Button::onHoverExit(int _x, int _y) {
    image->mouseX = getMouseXInterval(_x);
    image->mouseY = getMouseYInterval(_y);
}

bool Button::isPointerInside(int _x, int _y)
{
    int x = image->x;
    int y = image->y;
    int w = image->width;
    int h = image->height;
    return _x >= x && _x < x + w && _y >= y && _y < y + h;
}

void Button::setSize(int _width, int _height)
{
    image->width = _width;
    image->height = _height;
}

void Button::setPosition(int _x, int _y)
{
    image->x = _x;
    image->y = _y;
}

void Button::centerText(Graphics& _graphics)
{
    int textW = text.getPixelWidth(_graphics);
    int textH = text.getPixelHeight();
    int btnX = image->x;
    int btnY = image->y;
    int btnW = image->width;
    int btnH = image->height;
    text.x = btnX + (btnW / 2) - (textW / 2);
    text.y = btnY + (std::max<int>((btnH - textH), 0) / 2) + (int) ceilf((float)text.getPixelHeight()/10.0f);
}

glm::vec3 Button::getHighlightColor()
{
    if (!active)
        return nullColor;
    return highlightColor;
}
glm::vec3 Button::getPressedColor()
{
    if (!active)
        return nullColor;
    return pressedColor;
}
glm::vec3 Button::getDefaultColor()
{
    return defaultColor;
}

void Button::setHoldPress(bool _holdPress)
{
    holdPress = _holdPress;
}

bool Button::isHoldingPress()
{
    return holdPress;
}

void Button::update(int _x, int _y, bool _isPress, bool _isRelease)
{
    onHover(_x, _y);
    if (_isPress)
        onPress(_x, _y);
    if (_isRelease)
        onRelease(_x, _y);
    shaderTimer.forwardAnimation = highlighted;
    shaderTimer.backAnimation = !highlighted;
}

void Button::update(Graphics& _graphics, Mouse& _mouse)
{
    int globalX = _mouse.x;
    int globalY = _mouse.y;
    std::pair<int, int> relativeMousePosition = _graphics.getPixelPosition(globalX, globalY, viewIndex);
    update(relativeMousePosition.first, relativeMousePosition.second, _mouse.isLeftPress, _mouse.isLeftReleased);
}

float Button::getMouseXInterval(int _x) {
    if (_x < getX())
        return 0.0f;
    if (_x > getX() + getWidth())
        return 1.0f;
    return (float)(_x - getX()) / (float)getWidth();
}

float Button::getMouseYInterval(int _y) {
    if (_y < getY())
        return 1.0f;
    if (_y > getY() + getHeight())
        return 0.0f;
    return 1.0f - (float)(_y - getY()) / (float)getHeight();
}

void Button::render(Graphics& _graphics, Mouse& _mouse) {
    shaderTimer.updateEffectInterpolation();
    image->effect = shaderTimer.effectInterpolation;
    image->isHighlighted = highlighted && active;
    image->render(_graphics);
    text.render(_graphics);
}

void Button::setActive(bool _isActive) {
    active = _isActive;
}

bool Button::isHighlighted() {
    return highlighted;
}

bool Button::isActive() {
    return active;
}

void Button::setColor(glm::vec3 _color) {
    defaultColor = _color;
}

void Button::setTextColor(glm::vec3 _color) {
    text.setColor(_color);
}

void Button::setText(std::string _text) {
    text.setText(_text);
}

void Button::setTextPixelHeight(int _pixelHeight) {
    text.setPixelHeight(_pixelHeight);
}

int Button::getWidth() {
    return image->width;
}
int Button::getHeight() {
    return image->height;
}

void Button::setDark(bool _dark) {
    image->grayscale = _dark;
    image->darken = _dark;
}

void Button::setGray(bool _gray) {
    image->grayscale = _gray;
}

void Button::setBorderSize(int _size) {
    image->borderSize = _size;
}

void Button::setTexture(std::string _texture) {
    image->texture = _texture;
}

void Button::setBorderColor(glm::vec3 _color) {
    image->singleColor = _color;
}
void Button::setAlpha(float _alpha) {
    image->alpha = _alpha;
}

int Button::getX() {
    return image->x;
}

int Button::getY() {
    return image->y;
}
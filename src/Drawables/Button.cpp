#include "Button.h"
#include <iostream>

Button::Button() {
    text.pixelHeight = 30;
    setTextPositionCenter();
    text.color = glm::vec4(0.8f,0.8f,0.8f,1.0f);
    image.texture = "button1.png";
    image.width = 300;
}

void Button::setTextPositionCenter() {
    int textW = text.estimateWidth();
    int textH = text.pixelHeight;
    int btnX = image.x;
    int btnY = image.y;
    int btnW = image.width;
    int btnH = image.height;
    text.x = btnX + (btnW / 2) - (textW / 2);
    text.y = btnY + (btnH / 2) - (textH / 2);
}

void Button::onPress(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        isPressed = true;
        image.extraColor = pressedColor;
    }
    else {
        isPressed = false;
        image.extraColor = defaultColor;
    }
}
void Button::onRelease(int _x, int _y) {
    if (isPressed && isPointerInside(_x, _y) && onPressCallback) {
        onPressCallback();
    }
    image.extraColor = defaultColor;
    isPressed = false;
    onHover(_x, _y);
}

void Button::onHover(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        image.isHighlighted = true;
        if(!isPressed)
            image.extraColor = highlightColor;
    }
    else {
        image.isHighlighted = false;
        if(!isPressed)
            image.extraColor = defaultColor;
    }
}

bool Button::isPointerInside(int _x, int _y) {
    int x = image.x;
    int y = image.y;
    int w = image.width;
    int h = image.height;
    return _x >= x && _x <= x + w && _y >= y && _y <= y + h;
}

void Button::setSize(int _width, int _height) {
    image.width = _width;
    image.height = _height;
}

void Button::setPosition(int _x, int _y) {
    image.x = _x;
    image.y = _y;
    setTextPositionCenter();
}


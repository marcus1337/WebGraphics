#include "Button.h"
#include <iostream>

void Button::onPress(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        std::cout << "inside...\n";
    }

}
void Button::onRelease(int _x, int _y) {
    if (isClicked && onPressCallback) {
        onPressCallback();
    }
}

void Button::onHover(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        image.isHighlighted = true;
    }
    else {
        image.isHighlighted = false;
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
    text.x = _x;
    text.y = _y;
}

Image Button::getImage() {
    return image;
}

Text Button::getText() {
    return text;
}

#include "Window/InputDevices/Mouse.h"
#include <GLFW/glfw3.h>
#include <iostream>


Mouse::Mouse() {
    buttons[MouseButton::LEFT] = ButtonState();
    buttons[MouseButton::RIGHT] = ButtonState();
}


void Mouse::addDrag(int _x, int _y) {
    xDragDelta += _x - x;
    yDragDelta += y - _y; // reversed since y-coordinates go from bottom to top
    x = _x;
    y = _y;
}

double Mouse::getX() {
    return x;
}

double Mouse::getY() {
    return y;
}

double Mouse::getDragDeltaX() {
    return xDragDelta;
}

double Mouse::getDragDeltaY() {
    return yDragDelta;
}

double Mouse::getScrollDelta() {
    return scrollDelta;
}

void Mouse::addScroll(double _scrollDelta) {
    scrollDelta += _scrollDelta;
}

void Mouse::onButtonPress(MouseButton btn) {
    buttons[btn].pressed = true;
    buttons[btn].pressEvent = true;
}

void Mouse::onButtonLift(MouseButton btn) {
    buttons[btn].pressed = false;
    buttons[btn].unPressEvent = true;
}

bool Mouse::isPressed(MouseButton btn) {
    return buttons[btn].pressed;
}

bool Mouse::isPressEvent(MouseButton btn) {
    return buttons[btn].pressEvent;
}

bool Mouse::isUnPressEvent(MouseButton btn) {
    return buttons[btn].unPressEvent;
}

void Mouse::reset()
{
    for (auto& [key, value] : buttons) {
        value.clearEvents();
    }
    xDragDelta = 0;
    yDragDelta = 0;
    scrollDelta = 0;
    x = 0;
    y = 0;
}
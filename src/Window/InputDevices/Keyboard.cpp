#include "Window/InputDevices/Keyboard.h"
#include <iostream>

void Keyboard::clearEvents() {
    for (std::size_t i = 0; i < NUM_KEYS; i++) {
        buttons->clearEvents();
    }
}

bool Keyboard::isPressed(int key) {
    return buttons[key].pressed;
}

bool Keyboard::isPressEvent(int key) {
    return buttons[key].pressEvent;
}

bool Keyboard::isUnPressEvent(int key) {
    return buttons[key].unPressEvent;
}

void Keyboard::onButtonPress(int key) {
    buttons[key].pressEvent = true;
    buttons[key].pressed = true;
}

void Keyboard::onButtonLift(int key) {
    buttons[key].pressed = false;
    buttons[key].unPressEvent = true;
}

void Keyboard::bindKey(int key, std::function<void(ButtonState)> func) {
    keyBindings[key] = func;
}

void Keyboard::handleBindings() {
    for (auto& [key, func] : keyBindings) {
        func(buttons[key]);
    }
}
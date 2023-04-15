#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <GLFW/glfw3.h>
#include <cstddef>
#include "ButtonState.h"
#include <map>
#include <functional>

class Keyboard
{
    static constexpr std::size_t NUM_KEYS = 350;
    ButtonState buttons[NUM_KEYS] = {};
    std::map<int, std::function<void(ButtonState)>> keyBindings;
    bool quitProgram = false;

    void clearEvents();
    void onButtonPress(int key);
    void onButtonLift(int key);
    void handleBindings();

    friend class Canvas;
    friend class CanvasCallbacks;

public:
    bool isPressed(int key);
    bool isPressEvent(int key);
    bool isUnPressEvent(int key);
    void bindKey(int key, std::function<void(ButtonState)> func);
};

#endif
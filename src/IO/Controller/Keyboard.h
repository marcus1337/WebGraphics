#include <GLFW/glfw3.h>
#include <cstddef>

#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
    static constexpr std::size_t numKeys = 350;
    bool isPressed[numKeys] = {};
    bool isDownClick[numKeys] = {};
    bool isUpClick[numKeys] = {};

public:

    void setKeys(GLFWwindow* window, int key, int scancode, int action, int mods);
    bool quitProgram = false;
    void reset();

};

#endif
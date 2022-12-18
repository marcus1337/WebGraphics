#include "Keyboard.h"
#include <iostream>

void Keyboard::setKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        isDownClick[key] = true;

    for (std::size_t i = 0; i < numKeys; i++)
        isPressed[i] = glfwGetKey(window, i) == GLFW_PRESS;

    if (action == GLFW_RELEASE)
        isUpClick[key] = true;

    if (isDownClick[GLFW_KEY_ESCAPE])
        quitProgram = true;
}

void Keyboard::reset() {
    for (std::size_t i = 0; i < numKeys; i++) {
        isDownClick[i] = isUpClick[i] = false;
    }
}

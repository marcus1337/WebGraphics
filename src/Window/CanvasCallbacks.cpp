#include "Window/CanvasCallbacks.h"
#include <iostream>

auto CanvasCallbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    CanvasCallbacks* mw = static_cast<CanvasCallbacks*>(glfwGetWindowUserPointer(window));

    MouseButton mouseBtn = MouseButton::LEFT;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
        mouseBtn = MouseButton::LEFT;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        mouseBtn = MouseButton::RIGHT;
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        mouseBtn = MouseButton::MIDDLE;

    if (action == GLFW_RELEASE) {
        mw->mouse->onButtonLift(mouseBtn);
    }else if (action == GLFW_PRESS) {
        mw->mouse->onButtonPress(mouseBtn);
    }
}

auto CanvasCallbacks::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    CanvasCallbacks* mw = static_cast<CanvasCallbacks*>(glfwGetWindowUserPointer(window));
    mw->mouse->addDrag((int)xpos, mw->canvasSettings->height - 1 - (int)ypos);
}

auto CanvasCallbacks::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    CanvasCallbacks* mw = static_cast<CanvasCallbacks*>(glfwGetWindowUserPointer(window));
    mw->mouse->addScroll(yoffset);
}

auto CanvasCallbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CanvasCallbacks* mw = static_cast<CanvasCallbacks*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS) {
        mw->keyboard->onButtonPress(key);
    }
    else if (action == GLFW_RELEASE) {
        mw->keyboard->onButtonLift(key);
    }
}

auto CanvasCallbacks::window_size_callback(GLFWwindow* window, int width, int height)
{
    CanvasCallbacks* mw = static_cast<CanvasCallbacks*>(glfwGetWindowUserPointer(window));
    mw->canvasSettings->width = width;
    mw->canvasSettings->height = height;
    glViewport(0, 0, width, height);
    if (mw->resizeCallbackFunction)
        mw->resizeCallbackFunction();
}

void CanvasCallbacks::set(GLFWwindow* _window, Mouse* _mouse, Keyboard* _keyboard, CanvasSettings* _canvasSettings) {
    window = _window;
    mouse = _mouse;
    keyboard = _keyboard;
    canvasSettings = _canvasSettings;

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

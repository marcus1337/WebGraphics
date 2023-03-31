
#ifndef CANVASCALLBACKS_H
#define CANVASCALLBACKS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "InputDevices/Mouse.h"
#include "InputDevices/Keyboard.h"
#include <functional>
#include "CanvasSettings.h"

class CanvasCallbacks {

    inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos);
    inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    inline static auto window_size_callback(GLFWwindow* window, int width, int height);

public:
    Mouse* mouse;
    Keyboard* keyboard;
    GLFWwindow* window;
    CanvasSettings* canvasSettings;
    std::function<void(void)> resizeCallbackFunction;

    void set(GLFWwindow* _window, Mouse* _mouse, Keyboard* _keyboard, CanvasSettings* _canvasSettings);
};

#endif
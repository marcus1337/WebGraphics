

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "IO/Controller/Mouse.h"
#include "IO/Controller/Keyboard.h"
#include "AspectRatio.h"
#include <functional>

#ifndef CANVAS_H
#define CANVAS_H

class Canvas {

    inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos);
    inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    inline static auto window_size_callback(GLFWwindow* window, int width, int height);

    void SetVSync(bool sync);
    void setWindowHints();
    void setWindowCallbacks(GLFWwindow* window);

    bool initGLFW();
    GLFWwindow* window;
    bool initWindow();
    void setIconImage();

public:
    std::function<void(void)> appResizeCallbackFunction;
    AspectRatio aspectRatio;
    void resizeWindow(int width, int height);
    void autoScreenResize(double yoffset);
    int width = 1280;
    int height = 720;
    Mouse mouse;
    Keyboard keyboard;
    Canvas();
    ~Canvas();
    bool hasQuit();
    void display();
    void pollEvents();
};

#endif
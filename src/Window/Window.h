
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "IO/Controller/Mouse.h"
#include "IO/Controller/Keyboard.h"
#include "AspectRatio.h"

#ifndef MYWINDOW_H
#define MYWINDOW_H

class Window {

    inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos);
    inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    inline static auto window_size_callback(GLFWwindow* window, int width, int height);

    void SetVSync(bool sync);
    void setWindowHints();
    void setWindowCallbacks(GLFWwindow* window);

    void scrollScreenResize(double yoffset);
    bool initGLFW();
    GLFWwindow* window;
    bool initWindow();

public:
    //void resizeToAspectRatio();
    AspectRatio aspectRatio;
    void resizeWindow(int width, int height);
    int width = 800;
    int height = 600;
    Mouse mouse;
    Keyboard keyboard;
    Window();
    ~Window();
    bool hasQuit();
    void display();
    void pollEvents();
};

#endif
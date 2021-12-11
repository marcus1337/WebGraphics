


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include <map>
#include <string>
#include "IO/Controller/Mouse.h"
#include "IO/Controller/Keyboard.h"

#ifndef MYWINDOW_H
#define MYWINDOW_H

class MyWindow {

    inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos);
    inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    inline static auto window_size_callback(GLFWwindow* window, int width, int height);

    void SetVSync(bool sync);
    void setWindowHints();
    void setWindowCallbacks(GLFWwindow* window);

public:
    void resizeWindow(int width, int height);

    GLFWwindow* window;
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    Mouse mouse;
    Keyboard keyboard;

    bool initWindow();
    bool initGLFW();

    MyWindow();
    ~MyWindow();
};

#endif
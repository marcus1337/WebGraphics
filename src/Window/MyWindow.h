


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include <map>
#include <string>
#include "Mouse.h"

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

    bool quitProgram = false;
    bool goForward = false;
    bool goBack = false;
    bool goLeft = false;
    bool goRight = false;
    bool rotateRight = false;
    bool rotateLeft = false;

    GLFWwindow* window;
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    Mouse mouse;

    static void debugKeys(MyWindow* mywindow, GLFWwindow* window);

    void moveCamera(Camera& camera);
    bool initWindow();
    bool initGLFW();

    MyWindow();
    ~MyWindow();
};

#endif



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include <map>
#include <string>

#ifndef MYWINDOW_H
#define MYWINDOW_H

class MyWindow {

    inline static auto mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

public:

    bool increaseZoom = false;
    bool decreaseZoom = false;

    bool isLeftMousePressed = false;
    bool wasLeftMousePressed = false;
    bool wasLeftMouseReleased = false;

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

    Camera camera;
    float lastX = 0.0f;
    float lastY = 0.0f;
    float relativeMouseX = 0.0f;
    float relativeMouseY = 0.0f;
    bool firstMouse = true;

    glm::vec2 getRelativeMousePosition();

    MyWindow();
    ~MyWindow();
    inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void setRelMousePos(float _fromX = 0.f, float _fromY = 0.f, float _toX = 1.f, float _toY = 1.f);
    inline static auto scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    inline static auto window_size_callback(GLFWwindow* window, int width, int height);
    static void debugKeys(MyWindow* mywindow, GLFWwindow* window);

    void processActions();
    bool initWindow();
    bool initGLFW();

    glm::mat4 projection, view;
    void handleFrame();
    float P11 = 1.f;

};

#endif
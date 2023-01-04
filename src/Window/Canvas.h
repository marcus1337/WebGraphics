

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "InputDevices/Mouse.h"
#include "InputDevices/Keyboard.h"
#include <functional>
#include "CanvasCallbacks.h"
#include "CanvasSettings.h"

#ifndef CANVAS_H
#define CANVAS_H

class Canvas {

    void SetVSync(bool sync);
    void setWindowHints();

    bool initGLFW();
    CanvasCallbacks canvasCallbacks;
    CanvasSettings canvasSettings;
    GLFWwindow* window;

public:
    void setTitle(std::string _title);
    void setResizeCallbackFunction(std::function<void(void)> _function);
    void resizeWindow(int width, int height);
    Mouse mouse;
    Keyboard keyboard;
    Canvas();
    ~Canvas();
    bool hasQuit();
    void display();
    void pollEvents();
    int getWidth();
    int getHeight();

    void setFullScreen(bool _fullScreen);
    bool isFullScreen();

    void setIconImage(GLFWimage& image);
};

#endif
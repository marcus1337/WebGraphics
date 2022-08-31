

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "IO/Controller/Mouse.h"
#include "IO/Controller/Keyboard.h"
#include <functional>
#include "CanvasCallbacks.h"
#include "CanvasSettings.h"

#ifndef CANVAS_H
#define CANVAS_H

class Canvas {

    void SetVSync(bool sync);
    void setWindowHints();

    bool initGLFW();
    GLFWwindow* window;
    void setIconImage();
    CanvasCallbacks canvasCallbacks;
    CanvasSettings canvasSettings;

public:
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
};

#endif
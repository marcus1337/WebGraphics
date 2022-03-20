#include "Utility/GLData.h"
#include "Window/Window.h"
#include "Window/Image.h"
#include "Utility/MatrixData.h"
#include "Window/ImageUniform.h"
#include "Window/PostImageUniform.h"
#include "Window/Text.h"
#include "Window/Framebuffer.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <vector>

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Window window;
private:
    Camera camera;
    Image image;
    ImageUniform* imageUniform = nullptr;
    Framebuffer framebuffer;

    Text text;
    GLData glData;

    void drawStep();
    void endDraw();
    void beginDraw();
    void setGLSettings();

public:
    Engine();
    ~Engine();

    void draw();
    void resizeWindow(int _width, int _height);
    void pollEvents();
};

#endif // !ENGINE_H

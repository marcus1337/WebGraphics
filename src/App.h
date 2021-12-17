#include "Utility/GLData.h"
#include "Window/MyWindow.h"
#include "Window/Image.h"
#include "Utility/MatrixData.h"
#include "Window/ImageUniform.h"
#include "Window/PostImageUniform.h"
#include "Window/Text.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

#ifndef APP_H
#define APP_H

class App
{
    MyWindow mywindow;
    Camera camera;
    Image image;
    ImageUniform *imageUniform = nullptr;
    PostImageUniform *postImageUniform = nullptr;

    Text text;
    GLData glData;
    MatrixData matrixdata;

    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    void prepareUpdate();
    void update();
    bool isGameUpdate();

    void drawStep();
    void endDraw();
    void beginDraw();

    void setGLSettings();

public:
    App();
    ~App();
    void draw();
    void run();
    void step();
    void resizeWindow(int _width, int _height);
};

#endif
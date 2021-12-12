#include "Utility/GLData.h"
#include "Window/MyWindow.h"
#include "Window/Image.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

#include "Utility/MatrixData.h"
#include "IO/Files/IOTexture.h"

#include "Window/ImageUniform.h"
#include "Window/Text.h"


#ifndef APP_H
#define APP_H

class App {

    MyWindow mywindow;
    Camera camera;
    Image image;
    ImageUniform* imageUniform = nullptr;
    Text text;

    GLData glData;
    MatrixData matrixdata;
    IOTexture iotexture;

    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    TextureData textureData;

    void prepareUpdate();
    void update();
    bool isGameUpdate();

    void drawStep();
    void endDraw();
    void beginDraw();

    void gameStep();

public:
    App();
    ~App();
    void draw();
    void run();
    void step();

    void resizeWindow(int _width, int _height);
};

#endif
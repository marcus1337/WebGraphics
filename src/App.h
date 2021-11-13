#include "Utility/GLData.h"
#include "IO/IOStuff.h"
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
#include "IO/IOStuff.h"
#include "IO/IOShader.h"
#include "IO/IOTexture.h"


#ifndef APP_H
#define APP_H

class App {

    Camera camera;

    GLData glData;
    MatrixData matrixdata;
    Image image;
    MyWindow mywindow;
    IOStuff iostuff;
    IOShader ioshader;
    IOTexture iotexture;

    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    void prepareUpdate();
    void update();
    void init();
    bool isGameUpdate();

    TextureData textureData;

public:

    void gameStep();

    App();
    ~App();
    void drawStep();
    void endDraw();
    void beginImGuiDraw();
    void beginDraw();
    void run();

    void resizeWindow(int _width, int _height);

};

#endif
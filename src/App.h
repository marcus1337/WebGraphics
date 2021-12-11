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

    MyWindow mywindow;
    Camera camera;
    Image image;

    GLData glData;
    MatrixData matrixdata;
    IOStuff iostuff;
    IOShader ioshader;
    IOTexture iotexture;

    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    TextureData textureData;
    std::vector<ShaderData> shaders;

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
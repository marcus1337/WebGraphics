
#include "IO/IO.h"
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

#include "Model/Model.h"
#include "Model/MatrixData.h"
#include "Model/ModelManager.h"


#ifndef APP_H
#define APP_H

class App {

    Camera camera;

    IO io;
    MatrixData matrixdata;
    Image image;
    MyWindow mywindow;
    ModelManager modelManager;

    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    void updatePage();
    void init();
    bool isGameUpdate();

    int monitorRefreshRate;
    static bool keepRunning;
    void onWindowResize();
    uint64_t getTicks();

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
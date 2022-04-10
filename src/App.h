#include "Engine/Engine.h"

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
    Engine engine;
    long long passedFrameTime, frameTime;
    std::chrono::steady_clock::time_point timeLastUpdateCheck;

    void updateLogic();
    bool isUpdate();
    void renderViews();
    void render();

public:
    App();
    ~App();
    void run();
    void update();
    void resizeWindow(int _width, int _height);
};

#endif
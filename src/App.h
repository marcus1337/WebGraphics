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
    uint64_t gameTicks = 0;
    long long MS_FRAME;
    long long MS_PASSED;
    std::chrono::steady_clock::time_point timeSinceGameUpdate;

    void update();
    bool isGameUpdate();

public:
    App();
    ~App();
    void run();
    void step();
    void resizeWindow(int _width, int _height);
};

#endif
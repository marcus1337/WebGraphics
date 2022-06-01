#include "Engine/Engine.h"
#include "UpdateTimer.h"
#include <string>

#ifndef APP_H
#define APP_H

class App
{
    UpdateTimer updateTimer;
    Engine engine;

    void updateLogic();
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
#define GLEW_STATIC
#include <GL/glew.h>

#include "Engine/Engine.h"
#include "UpdateTimer.h"
#include <string>

#include "Panels/Panel.h"
#include <stack>
#include "DevController.h"

#ifndef APP_H
#define APP_H

class App
{
    UpdateTimer updateTimer;
    Engine engine;
    std::stack<Panel*> panels;
    DevController devController;

    void updateLogic();
    void render();
    void handlePanelChange();

public:
    App();
    ~App();
    void run();
    void update();
    void resizeWindow(int _width, int _height);
};

#endif
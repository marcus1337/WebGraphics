#define GLEW_STATIC
#include <GL/glew.h>

#include "Engine/Engine.h"
#include "UpdateTimer.h"
#include <string>

#include "Panels/PanelHandler.h"
#include <stack>

#ifndef APP_H
#define APP_H

class App
{
    UpdateTimer updateTimer;
    Engine engine;
    PanelHandler panelHandler;
    void render();

public:
    App();
    ~App();
    void loop();
    void loopStep();
    void resizeWindow(int _width, int _height);
};

#endif
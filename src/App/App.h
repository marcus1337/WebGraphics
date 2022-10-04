#define GLEW_STATIC
#include <GL/glew.h>

#include "Engine/Engine.h"
#include "UpdateTimer.h"
#include <string>

#include "Panels/PanelHandler.h"
#include <stack>
#include "ShaderUpdater.h"

#ifndef APP_H
#define APP_H

class App
{
    UpdateTimer updateTimer;
    Engine engine;
    PanelHandler panelHandler;
    ShaderUpdater shaderUpdater;
    void render();

public:
    App();
    ~App();
    void run();
    void update();
    void resizeWindow(int _width, int _height);
};

#endif
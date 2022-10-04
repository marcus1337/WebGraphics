
#include "App.h"
#include <iostream>

App::App() : shaderUpdater(engine), panelHandler(engine) {
}


App::~App() {
}

void App::run()
{
    while (!engine.window.hasQuit())
    {
        if (updateTimer.isRenderUpdate())
            update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::resizeWindow(int _width, int _height)
{
    engine.window.resizeWindow(_width, _height);
}

void App::update() { 
    if (updateTimer.isLogicUpdate()) {
        panelHandler.update();
        engine.window.pollEvents();
        shaderUpdater.update();
    }
    render();
}

void App::render() {
    engine.graphics.clearView();
    panelHandler.render();
    engine.graphics.display();
}

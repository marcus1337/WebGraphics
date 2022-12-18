
#include "App.h"
#include <iostream>

App::App() : panelHandler(engine) {
}


App::~App() {
}

void App::loop()
{
    while (!engine.window.hasQuit())
    {
        loopStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::resizeWindow(int _width, int _height)
{
    engine.window.resizeWindow(_width, _height);
}

void App::loopStep() {
    if (updateTimer.isLogicUpdate()) {
        panelHandler.update();
        engine.window.pollEvents();
    }
#ifndef EMSCRIPTEN 
    if (updateTimer.isRenderUpdate())
#endif
        render();
}

void App::render() {
    engine.graphics.mainView.clear();
    panelHandler.render();
    engine.graphics.mainView.display();
}

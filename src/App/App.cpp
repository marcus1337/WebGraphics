
#include "App.h"
#include <iostream>
#include "Drawables/Button.h"

App::App() : mainMenu(engine) {

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

void App::update(){
    if (updateTimer.isLogicUpdate()) {
        updateLogic();
        engine.window.pollEvents();
    }
    render();
}

void App::updateLogic() {
    mainMenu.update();
}

void App::render() {
    engine.graphics.clearViews();
    renderViews();
    engine.graphics.display();
}

void App::renderViews(){
    mainMenu.render();
}
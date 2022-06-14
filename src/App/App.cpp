
#include "App.h"
#include <iostream>
#include "Drawables/Button.h"

App::App() {
    panels.push(new MainMenu(engine));
}

App::~App() {
    while (!panels.empty()) {
        Panel* panel = panels.top();
        delete panel;
        panels.pop();
    }
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
        if (panels.top()->panelStatus == PanelStatus::FINISHED) {
            delete panels.top();
            panels.pop();
        }

        Panel* childPanel = panels.top()->childPanel;
        if (childPanel != nullptr) {
            panels.top()->childPanel = nullptr;
            panels.push(childPanel);
        }

        updateLogic();
        engine.window.pollEvents();
    }
    render();
}

void App::updateLogic() {
    panels.top()->update();
}

void App::render() {
    engine.graphics.clearViews();
    renderViews();
    engine.graphics.display();
}

void App::renderViews(){
    panels.top()->render();
}
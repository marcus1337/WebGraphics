
#include "App.h"
#include <iostream>
#include "App/Panels/Main/MainMenu.h"

App::App() : devController(engine) {
    panels.push(new MainMenu(engine));
    panels.top()->onEnter();
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

void App::handlePanelChange() { //assume MainMenu is always the base panel.
    if (panels.top()->panelStatus == PanelStatus::FINISHED) {
        delete panels.top();
        panels.pop();
        panels.top()->onEnter();
    }

    Panel* childPanel = panels.top()->childPanel;
    if (childPanel != nullptr) {
        panels.top()->childPanel = nullptr;
        panels.push(childPanel);
        panels.top()->onEnter();
    }
}

void App::update() { 
    handlePanelChange();
    if (updateTimer.isLogicUpdate()) {
        updateLogic();
        engine.window.pollEvents();
        devController.update();
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

void App::renderViews() {
    panels.top()->render();
}
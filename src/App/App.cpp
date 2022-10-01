
#include "App.h"
#include <iostream>
#include "App/Panels/Main/MainMenuPanel.h"

App::App() : shaderUpdater(engine) {
    panels.push(new MainMenuPanel(engine));
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

void App::handlePanelChange() {
    if (panels.size() > 1 && panels.top()->isDone()) {
        delete panels.top();
        panels.pop();
        panels.top()->onEnter();
    }

    Panel* childPanel = panels.top()->getChildPanel();
    if (childPanel != nullptr) {
        panels.push(childPanel);
        panels.top()->onEnter();
    }
}

void App::update() { 
    handlePanelChange();
    if (updateTimer.isLogicUpdate()) {
        updateLogic();
        engine.window.pollEvents();
        shaderUpdater.update();
    }
    render();
}

void App::updateLogic() {
    panels.top()->update();
    panels.top()->updateUI();
}

void App::render() {
    engine.graphics.clearView();
    panels.top()->render();
    panels.top()->renderUI();
    engine.graphics.display();
}

#include "PanelHandler.h"

PanelHandler::PanelHandler(Engine& _engine) : engine(_engine) {
    panels.push(new MainMenuPanel(engine));
    panels.top()->onEnter();
}
PanelHandler::~PanelHandler() {
    while (!panels.empty()) {
        Panel* panel = panels.top();
        delete panel;
        panels.pop();
    }
}
void PanelHandler::update() {
    panels.top()->update();
    panels.top()->updateUI();
    changePanel();
}
void PanelHandler::render() {
    panels.top()->render();
    panels.top()->renderUI();
}

void PanelHandler::changePanel() {
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
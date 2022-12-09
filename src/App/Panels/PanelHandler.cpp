#include "PanelHandler.h"

PanelHandler::PanelHandler(Engine& _engine) : engine(_engine), panelFactory(_engine) {
    panels.push(panelFactory.getNewPanel(PanelType::GAME));
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
    changePanel();
}

void PanelHandler::render() {
    panels.top()->render();
}

void PanelHandler::changePanel() {
    if (panels.size() > 1 && panels.top()->isDone()) {
        delete panels.top();
        panels.pop();
        panels.top()->onEnter();
    }

    Panel* panel = panelFactory.getNewPanel(panels.top()->getChildPanel());
    if (panel != nullptr) {
        panels.top()->setChildPanel(PanelType::NONE);
        panels.push(panel);
        panels.top()->onEnter();
    }
}


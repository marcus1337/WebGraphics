#include "Panel.h"

Panel::Panel(Engine& _engine) : panelStatus(PanelStatus::RUNNING), engine(_engine) {

}

void Panel::updateButtons(int _x, int _y) {
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->onHover(_x, _y);
        if (engine.window.mouse.isLeftPress) {
            buttons[i]->onPress(_x, _y);
        }
        if (engine.window.mouse.isLeftReleased) {
            buttons[i]->onRelease(_x, _y);
        }
    }
}

void Panel::renderButtons() {
    for (Button* btn : buttons) {
        engine.graphics.drawImage(btn->image);
        engine.graphics.drawText(btn->text);
    }
}

int Panel::getRelativeMouseXPosition() {
    int globalX = engine.window.mouse.x;
    int globalY = engine.window.mouse.y;
    std::pair<int, int> relativeMousePosition = engine.graphics.getPixelPosition(globalX, globalY);
    return relativeMousePosition.first;
}

int Panel::getRelativeMouseYPosition() {
    int globalX = engine.window.mouse.x;
    int globalY = engine.window.mouse.y;
    std::pair<int, int> relativeMousePosition = engine.graphics.getPixelPosition(globalX, globalY);
    return relativeMousePosition.second;
}

void Panel::onExit() {
    panelStatus = PanelStatus::FINISHED;
}
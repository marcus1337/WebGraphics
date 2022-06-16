#include "Panel.h"

Panel::Panel(Engine& _engine) : panelStatus(PanelStatus::RUNNING), engine(_engine) {

}

void Panel::updateButtons(int _x, int _y) {
    for (int i = 0; i < buttons.size(); i++)
        updateButton(*buttons[i], _x, _y);
}

void Panel::renderButtons() {
    for (Button* button : buttons)
        renderButton(*button);
}

void Panel::updateButton(Button& button, int _x, int _y) {
    button.onHover(_x, _y);
    if (engine.window.mouse.isLeftPress) {
        button.onPress(_x, _y);
    }
    if (engine.window.mouse.isLeftReleased) {
        button.onRelease(_x, _y);
    }
}

void Panel::renderButton(Button& button) {
    engine.graphics.drawImage(button.image);
    engine.graphics.drawText(button.text);
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
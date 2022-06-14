#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(Engine& _engine) : Panel(_engine) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    backButton.onPressCallback = std::bind(&SettingsMenu::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(200, 100);
    backButton.setPosition(100, 50);
    buttons.push_back(&backButton);
}

void SettingsMenu::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void SettingsMenu::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
}


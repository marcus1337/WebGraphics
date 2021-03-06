
#include "GameViewOverlay.h"

GameViewOverlay::GameViewOverlay(Engine& _engine) : Panel(_engine), gameView(_engine) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    backButton.onPressCallback = std::bind(&GameViewOverlay::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(200, 100);
    backButton.setPosition(50, 50);
    buttons.push_back(&backButton);
}

void GameViewOverlay::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void GameViewOverlay::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
}
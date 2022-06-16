#include "LobbyMenu.h"

LobbyMenu::LobbyMenu(Engine& _engine, DemoLobbyNet& _lobbyNet) : Panel(_engine), lobbyNet(_lobbyNet) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    backButton.onPressCallback = std::bind(&LobbyMenu::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(200, 100);
    backButton.setPosition(50, 50);
    buttons.push_back(&backButton);
}

void LobbyMenu::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void LobbyMenu::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
}

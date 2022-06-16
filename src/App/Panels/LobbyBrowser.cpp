
#include "LobbyBrowser.h"

LobbyBrowser::LobbyBrowser(Engine& _engine, DemoLobbyNet& _lobbyNet) : Panel(_engine), lobbyNet(_lobbyNet) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    refreshButton.onPressCallback = std::bind(&LobbyBrowser::onRefresh, this);
    refreshButton.text.text = "Refresh";
    refreshButton.setSize(200, 100);
    refreshButton.setPosition(200, 50);

    backButton.onPressCallback = std::bind(&LobbyBrowser::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(200, 100);
    backButton.setPosition(50, 50);
    buttons.push_back(&backButton);
    buttons.push_back(&refreshButton);

    onRefresh();
}

LobbyButton LobbyBrowser::makeLobbyButton(NetID<int> lobbyID) {
    LobbyButton lbutton;
    lbutton.lobbyID = lobbyID;
    lbutton.button.onPressCallback = [&]() {
        std::cout << "lobby button press...\n";
    };
    lbutton.button.text.text = "Test Lobby";
    return lbutton;
}

void LobbyBrowser::setLobbyButtons() {
    lobbyButtons.clear();
    int lobbyIndex = 0;
    for (NetID<int> lobbyID : lobbyNet.getOpenLobbies()) {
        LobbyButton lobbyButton = makeLobbyButton(lobbyID);
        lobbyButton.button.setPosition(200, 200 + lobbyIndex * 40);
        lobbyButtons.push_back(lobbyButton);
        lobbyIndex++;
    }
}

void LobbyBrowser::onRefresh() {
    setLobbyButtons();
}

void LobbyBrowser::handleLobbyButtonClick() {

}

void LobbyBrowser::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
    for (LobbyButton& lobbyButton : lobbyButtons) {
        updateButton(lobbyButton.button, x, y);
    }
}

void LobbyBrowser::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
    for (LobbyButton& lobbyButton : lobbyButtons) {
        renderButton(lobbyButton.button);
    }
}



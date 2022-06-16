
#include "LobbyBrowser.h"

LobbyBrowser::LobbyBrowser(Engine& _engine, DemoLobbyNet& _lobbyNet) : Panel(_engine), lobbyNet(_lobbyNet) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    refreshButton.onPressCallback = std::bind(&LobbyBrowser::onRefresh, this);
    refreshButton.text.text = "Refresh";
    refreshButton.setSize(150, 70);
    refreshButton.setPosition(210, 50);

    backButton.onPressCallback = std::bind(&LobbyBrowser::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(150, 70);
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
    lbutton.background.texture = "background1.png";
    lbutton.description.text = "Host: " + lobbyNet.getUsername(lobbyNet.getLobbyHost());
    lbutton.button.setSize(100, 60);
    lbutton.background.width = 800;
    lbutton.background.height = 100;
    lbutton.description.pixelHeight = 30;
    lbutton.button.text.text = "JOIN";
    return lbutton;
}

void LobbyBrowser::setLobbyButtons() {
    lobbyButtons.clear();
    int lobbyIndex = 0;
    for (NetID<int> lobbyID : lobbyNet.getOpenLobbies()) {
        LobbyButton lbutton = makeLobbyButton(lobbyID);
        
        int xPos = 1250;
        int yPos = 960 - (lobbyIndex * 150);

        lbutton.button.setPosition(xPos, yPos);
        lbutton.background.x = xPos - lbutton.background.width + lbutton.button.image.width*2;
        lbutton.background.y = yPos - lbutton.button.image.height/3;
        lbutton.description.x = xPos - lbutton.background.width/2;
        lbutton.description.y = yPos + lbutton.description.pixelHeight/2;

        lobbyButtons.push_back(lbutton);
        lobbyIndex++;
        if (lobbyIndex >= 6)
            return;
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
    for (LobbyButton& lbutton : lobbyButtons) {
        engine.graphics.drawImage(lbutton.background);
        engine.graphics.drawText(lbutton.description);
        renderButton(lbutton.button);
    }
}



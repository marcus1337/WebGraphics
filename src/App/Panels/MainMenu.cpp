#include "MainMenu.h"
#include <iostream>
#include "SettingsMenu.h"
#include "AchievementsMenu.h"
#include "LobbyMenu.h"
#include "GameView.h"
#include "GameViewOverlay.h"
#include "LobbyBrowser.h"

MainMenu::MainMenu(Engine& _engine) : Panel(_engine) {

    backgroundImage.width = 1920;
    backgroundImage.height = 1080;

    singlePlayerButton.onPressCallback = std::bind(&MainMenu::onSinglePlayer, this);
    hostMultiPlayerButton.onPressCallback = std::bind(&MainMenu::onHostMultiPlayer, this);
    joinMultiPlayerButton.onPressCallback = std::bind(&MainMenu::onJoinMultiPlayer, this);
    settingsButton.onPressCallback = std::bind(&MainMenu::onSettings, this);
    achievementsButton.onPressCallback = std::bind(&MainMenu::onAchievements, this);
    quitButton.onPressCallback = std::bind(&MainMenu::onQuit, this);
    singlePlayerButton.text.text = "Solo Game";
    hostMultiPlayerButton.text.text = "Host Game";
    joinMultiPlayerButton.text.text = "Join Game";
    settingsButton.text.text = "Settings";
    achievementsButton.text.text = "Achievements";
    quitButton.text.text = "Quit";

    buttons.push_back(&singlePlayerButton);
    buttons.push_back(&hostMultiPlayerButton);
    buttons.push_back(&joinMultiPlayerButton);
    buttons.push_back(&settingsButton);
    //buttons.push_back(&achievementsButton);
    buttons.push_back(&quitButton);

    for (int i = 0; i < buttons.size(); i++) {
        int btnWidth = buttons[i]->image.width;
        int btnHeight = buttons[i]->image.height;
        buttons[i]->setPosition(1920 / 2 - btnWidth / 2, 700 - (i * btnHeight) - (25*i));
    }

    if (lobbyNet.setInviteLobbyID()) {
        if (childPanel == nullptr)
            childPanel = new LobbyMenu(engine, lobbyNet);
    }

}

void MainMenu::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void MainMenu::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
}

void MainMenu::onSinglePlayer() {
    std::cout << "onSinglePlayer()\n";
    if (childPanel == nullptr)
        childPanel = new GameViewOverlay(engine);
}

void MainMenu::onHostMultiPlayer() {
    std::cout << "onHostMultiPlayer()\n";
    if (childPanel == nullptr) {
        lobbyNet.createLobby();
        LobbyMenu * lobbyMenu = new LobbyMenu(engine, lobbyNet);
        childPanel = lobbyMenu;
    }
}

void MainMenu::onJoinMultiPlayer() {
    std::cout << "onJoinMultiPlayer()\n";
    if (childPanel == nullptr)
        childPanel = new LobbyBrowser(engine, lobbyNet);
}

void MainMenu::onSettings() {
    std::cout << "onSettings()\n";
    if(childPanel == nullptr)
        childPanel = new SettingsMenu(engine);
}

void MainMenu::onAchievements() {
    std::cout << "onAchievements()\n";
    if (childPanel == nullptr)
        childPanel = new AchievementsMenu(engine);
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}




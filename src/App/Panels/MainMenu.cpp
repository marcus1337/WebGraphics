#include "MainMenu.h"
#include <iostream>
#include "SettingsMenu.h"
#include "AchievementsMenu.h"
#include "LobbyMenu.h"
#include "GamePanel.h"

MainMenu::MainMenu(Engine& _engine) : Panel(_engine) {

    backgroundImage.width = 1920;
    backgroundImage.height = 1080;

    singlePlayerButton.onPressCallback = std::bind(&MainMenu::onSinglePlayer, this);
    multiPlayerButton.onPressCallback = std::bind(&MainMenu::onMultiPlayer, this);
    settingsButton.onPressCallback = std::bind(&MainMenu::onSettings, this);
    achievementsButton.onPressCallback = std::bind(&MainMenu::onAchievements, this);
    quitButton.onPressCallback = std::bind(&MainMenu::onQuit, this);
    singlePlayerButton.text.text = "SinglePlayer";
    multiPlayerButton.text.text = "MultiPlayer";
    settingsButton.text.text = "Settings";
    achievementsButton.text.text = "Achievements";
    quitButton.text.text = "Quit";

    buttons.push_back(&singlePlayerButton);
    buttons.push_back(&multiPlayerButton);
    buttons.push_back(&settingsButton);
    //buttons.push_back(&achievementsButton);
    buttons.push_back(&quitButton);

    for (int i = 0; i < buttons.size(); i++) {
        int btnWidth = buttons[i]->image.width;
        int btnHeight = buttons[i]->image.height;
        buttons[i]->setPosition(1920 / 2 - btnWidth / 2, 700 - (i * btnHeight) - (25*i));
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
        childPanel = new GamePanel(engine);
}

void MainMenu::onMultiPlayer() {
    std::cout << "onMultiPlayer()\n";
    if (childPanel == nullptr)
        childPanel = new LobbyMenu(engine);
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




#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : engine(_engine) {

    singlePlayerButton.onPressCallback = std::bind(&MainMenu::onStartSinglePlayer, this);
    multiPlayerButton.onPressCallback = std::bind(&MainMenu::onStartMultiPlayer, this);
    settingsButton.onPressCallback = std::bind(&MainMenu::onStartSettings, this);
    achievementsButton.onPressCallback = std::bind(&MainMenu::onStartAchievements, this);
    quitButton.onPressCallback = std::bind(&MainMenu::onQuit, this);
    singlePlayerButton.text.text = "SinglePlayer";
    multiPlayerButton.text.text = "MultiPlayer";
    settingsButton.text.text = "Settings";
    achievementsButton.text.text = "Achievements";
    quitButton.text.text = "Quit";

    buttons.push_back(&singlePlayerButton);
    buttons.push_back(&multiPlayerButton);
    buttons.push_back(&settingsButton);
    buttons.push_back(&achievementsButton);
    buttons.push_back(&quitButton);

    for (int i = 0; i < buttons.size(); i++) {
        int btnWidth = buttons[i]->image.width;
        int btnHeight = buttons[i]->image.height;
        buttons[i]->setPosition(1920 / 2 - btnWidth / 2, 900 - (i * btnHeight) - (50*i));
    }

}

void MainMenu::update() {
    int globalX = engine.window.mouse.x;
    int globalY = engine.window.mouse.y;
    std::pair<int, int> relativeMousePosition = engine.graphics.getPixelPosition(globalX, globalY);
    int x = relativeMousePosition.first;
    int y = relativeMousePosition.second;

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->onHover(x, y);
        if (engine.window.mouse.isLeftPress) {
            buttons[i]->onPress(x, y);
        }
        if (engine.window.mouse.isLeftReleased) {
            buttons[i]->onRelease(x, y);
        }
    }

}

void MainMenu::render() {
    engine.graphics.drawImage(backgroundImage);

    for (Button* btn : buttons) {
        engine.graphics.drawImage(btn->image);
        engine.graphics.drawText(btn->text);
    }

}

void MainMenu::onStartSinglePlayer() {
    std::cout << "onStartSinglePlayer()\n";
}

void MainMenu::onStartMultiPlayer() {
    std::cout << "onStartMultiPlayer()\n";
}

void MainMenu::onStartSettings() {
    std::cout << "onStartSettings()\n";
}

void MainMenu::onStartAchievements() {
    std::cout << "onStartAchievements()\n";
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}




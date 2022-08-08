#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : Panel(_engine) {

    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    quitButton.onPressCallback = std::bind(&MainMenu::onQuit, this);
    quitButton.setText("Quit");

    setMenuButtons();
}

void MainMenu::setMenuButtons() {
    buttons.clear();
    buttons.push_back(&quitButton);

    for (int i = 0; i < buttons.size(); i++) {
        buttons[i]->setSize(350, 70);
        int btnWidth = buttons[i]->getWidth();
        int btnHeight = buttons[i]->getHeight();
        buttons[i]->setPosition(1920 / 2 - btnWidth / 2, 700 - (i * btnHeight) - (25 * i));
        buttons[i]->centerText(engine.graphics);
    }
}

void MainMenu::update() {
    updateButtons();
}

void MainMenu::render() {
    backgroundImage.render(engine.graphics);
    renderButtons();
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";
    setMenuButtons();
}




#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : Panel(_engine) {

    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
}


void MainMenu::update() {

}

void MainMenu::render() {
    backgroundImage.render(engine.graphics);

}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}




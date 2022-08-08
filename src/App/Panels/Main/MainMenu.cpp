#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : Panel(_engine), backgroundImage(_engine) {
    backgroundImage.setSize(1920, 1080);
}


void MainMenu::update() {

}

void MainMenu::render() {
    backgroundImage.render();

}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}




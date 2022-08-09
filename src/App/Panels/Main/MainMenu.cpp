#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : Panel(_engine), backgroundImage(_engine), view(_engine, 500,500){
    backgroundImage.setSize(500, 500);
    view.paint(backgroundImage);
    Text text(_engine);
    text.setText("eyyy");
    text.setPosition(50, 250);
    text.setSize(1, 1);
    text.setPixelHeight(60);
    view.paint(text);
    backgroundImage.setSize(1920, 1080);
}


void MainMenu::update() {

}

void MainMenu::render() {
    backgroundImage.render();
    view.render();
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}




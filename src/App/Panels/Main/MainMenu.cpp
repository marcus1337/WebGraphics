#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu(Engine& _engine) : Panel(_engine), backgroundImage(_engine, "background3.png"), uiScript("main_menu", _engine) {
    backgroundImage.setSize(1920, 1080);
    uiScript.addMethod("onQuit", std::bind(&MainMenu::onQuit, this));
}

void MainMenu::update() {
    uiScript.update();
}

void MainMenu::render() {
    backgroundImage.render();
    uiScript.render();
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}






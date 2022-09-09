#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu(Engine& _engine) : Panel(_engine), uiScript("main_menu", _engine) {
    uiScript.addMethod("onQuit", std::bind(&MainMenu::onQuit, this));
}

void MainMenu::update() {
    uiScript.update();
}

void MainMenu::render() {
    uiScript.render();
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}






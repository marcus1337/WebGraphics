#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu(Engine& _engine) : Panel(_engine, "main_menu") {

}

void MainMenu::update() {
    uiScript.update();
}

void MainMenu::render() {
    uiScript.render();
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}






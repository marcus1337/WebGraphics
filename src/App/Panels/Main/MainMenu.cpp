#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Engine& _engine) : Panel(_engine), backgroundImage(_engine, "background1.png"), view(_engine, 500, 500), btn(_engine), uiScript("main_menu", _engine) {
    backgroundImage.setSize(500, 500);
    view.paint(backgroundImage);
    Text text(_engine);
    text.setText("eyyy2");
    text.setPosition(50, 250);
    text.setSize(1, 1);
    text.setPixelHeight(60);
    view.paint(text);
    backgroundImage.setSize(1920, 1080);

    btn.setPosition(500, 500);
    btn.onPressCallback = []() {
        std::cout << "pressed button...\n";
    };
}


void MainMenu::update() {
    btn.update();
    uiScript.update();
}

void MainMenu::render() {
    backgroundImage.render();
    view.render();
    btn.render();
    uiScript.render();
}

void MainMenu::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}




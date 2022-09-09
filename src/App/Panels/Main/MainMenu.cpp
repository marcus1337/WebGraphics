#include "MainMenu.h"
#include <iostream>
#include "SettingsPanel.h"

MainMenu::MainMenu(Engine& _engine) : Panel(_engine, "main_menu") {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenu::update() {

}
void MainMenu::render() {

}




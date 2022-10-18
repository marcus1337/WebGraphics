#include "MainMenuPanel.h"
#include <iostream>

MainMenuPanel::MainMenuPanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "main_menu", _panelContext) {
    uiScript.load();
}

void MainMenuPanel::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenuPanel::update() {

}
void MainMenuPanel::render() {

}




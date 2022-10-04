#include "MainMenuPanel.h"
#include <iostream>
#include "SettingsPanel.h"
#include "App/Panels/Lobby/LobbyPanel.h"
#include "App/Panels/Game/GamePanel.h"
#include "App/Panels/Lobby/LobbySearchPanel.h"
#include "InstructionsPanel.h"

MainMenuPanel::MainMenuPanel(Engine& _engine) : Panel(_engine, "main_menu") {
}

void MainMenuPanel::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenuPanel::update() {

}
void MainMenuPanel::render() {

}




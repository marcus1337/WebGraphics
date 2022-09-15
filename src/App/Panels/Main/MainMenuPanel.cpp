#include "MainMenuPanel.h"
#include <iostream>
#include "SettingsPanel.h"
#include "LobbyPanel.h"

MainMenuPanel::MainMenuPanel(Engine& _engine) : Panel(_engine, "main_menu") {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
    uiScript.addMethod("onLobby", [&]() {
        if (canSetChildPanel())
            setChildPanel(new LobbyPanel(engine));
        });
}

void MainMenuPanel::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenuPanel::update() {

}
void MainMenuPanel::render() {

}



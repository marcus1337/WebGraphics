#include "MainMenuPanel.h"
#include <iostream>
#include "SettingsPanel.h"
#include "LobbyPanel.h"
#include "GamePanel.h"
#include "LobbySearchPanel.h"
#include "InstructionsPanel.h"

MainMenuPanel::MainMenuPanel(Engine& _engine) : Panel(_engine, "main_menu") {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
    uiScript.addMethod("onLobby", [&]() {
        if (canSetChildPanel())
            setChildPanel(new LobbyPanel(engine));
        });
    uiScript.addMethod("onGame", [&]() {
        if (canSetChildPanel())
            setChildPanel(new GamePanel(engine));
        });
    uiScript.addMethod("onFindLobby", [&]() {
        if (canSetChildPanel())
            setChildPanel(new LobbySearchPanel(engine));
        });
    uiScript.addMethod("onInstructions", [&]() {
        if (canSetChildPanel())
            setChildPanel(new InstructionsPanel(engine));
        });
}

void MainMenuPanel::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenuPanel::update() {

}
void MainMenuPanel::render() {

}




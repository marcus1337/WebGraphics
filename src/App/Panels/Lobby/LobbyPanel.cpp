#include "LobbyPanel.h"
#include "App/Panels/Main/SettingsPanel.h"

void LobbyPanel::onEnter() {
    std::cout << "onEnter() Lobby\n";
}
LobbyPanel::LobbyPanel(Engine& _engine) : Panel(_engine, "lobby") {
    uiScript.addMethod("onSettings", [&]() {
        setChildPanel(PanelType::SETTINGS);
        });
}
void LobbyPanel::update() {

}
void LobbyPanel::render() {

}


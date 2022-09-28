#include "LobbyPanel.h"
#include "App/Panels/Main/SettingsPanel.h"

void LobbyPanel::onEnter() {
    std::cout << "onEnter() Lobby\n";
}
LobbyPanel::LobbyPanel(Engine& _engine) : Panel(_engine, "lobby") {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
    uiScript.addMethod("onLobby", [&]() {
        if (canSetChildPanel())
            setChildPanel(new LobbyPanel(engine));
        });
}
void LobbyPanel::update() {

}
void LobbyPanel::render() {

}


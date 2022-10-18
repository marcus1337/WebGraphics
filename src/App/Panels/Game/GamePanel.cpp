#include "GamePanel.h"
#include "App/Panels/Main/SettingsPanel.h"


void GamePanel::onEnter() {
    std::cout << "onEnter() GamePanel" << std::endl;
}
GamePanel::GamePanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "game", _panelContext) {
    uiScript.load();
}
void GamePanel::update() {

}

void GamePanel::render() {

}

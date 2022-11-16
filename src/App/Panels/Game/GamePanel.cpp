#include "GamePanel.h"

void GamePanel::onEnter() {
    std::cout << "onEnter() GamePanel" << std::endl;
}

GamePanel::GamePanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "game", _panelContext), chessScript(uiScript) {
    uiScript.load();
}

void GamePanel::update() {

}

void GamePanel::render() {

}

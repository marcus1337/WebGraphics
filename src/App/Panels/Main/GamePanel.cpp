#include "GamePanel.h"
#include "SettingsPanel.h"


void GamePanel::onEnter() {

}
GamePanel::GamePanel(Engine& _engine) : Panel(_engine, "game"), gameView(_engine, game) {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
}
void GamePanel::update() {
    game.tick();
}
void GamePanel::render() {
    gameView.render();
}

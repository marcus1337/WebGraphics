#include "GamePanel.h"


void GamePanel::onEnter() {

}
GamePanel::GamePanel(Engine& _engine) : Panel(_engine, "game"), gameView(_engine, game) {

}
void GamePanel::update() {
    game.tick();
}
void GamePanel::render() {
    gameView.render();
}

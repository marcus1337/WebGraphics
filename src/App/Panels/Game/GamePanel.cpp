#include "GamePanel.h"
#include "App/Panels/Main/SettingsPanel.h"


void GamePanel::onEnter() {
    std::cout << "onEnter() GamePanel" << std::endl;
}
GamePanel::GamePanel(Engine& _engine) : Panel(_engine, "game"), gameView(_engine, game), gameController(_engine, game) {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
}
void GamePanel::update() {
    gameController.update();
    game.tick();
}

void GamePanel::render() {
    //gameView.view.setSize(gameView.view.getPixelWidth(), gameView.view.getPixelHeight());
    gameView.paint();
    gameView.view.setPosition(1920 / 2 - gameView.view.getWidth() / 2, 1080 / 2 - gameView.view.getHeight() / 2);
    gameView.view.render();
}

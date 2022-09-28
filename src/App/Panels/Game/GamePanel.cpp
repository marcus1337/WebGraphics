#include "GamePanel.h"
#include "App/Panels/Main/SettingsPanel.h"


void GamePanel::onEnter() {

}
GamePanel::GamePanel(Engine& _engine) : Panel(_engine, "game"), gameView(_engine, game), gameController(_engine, game, gameCamera) {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
}
void GamePanel::update() {
    gameController.update();
    game.tick();
    game.tick();
    gameCamera.addZoomStep(engine.window.mouse.scrollDelta / 100.0f);
}

void GamePanel::render() {
    //gameView.view.setSize(gameView.view.getPixelWidth(), gameView.view.getPixelHeight());
    gameView.paint();
    gameView.view.setPosition(1920 / 2 - gameView.view.getWidth() / 2, 1080 / 2 - gameView.view.getHeight() / 2);
    gameView.view.render();
}

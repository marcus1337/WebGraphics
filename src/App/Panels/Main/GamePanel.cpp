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

    if (engine.window.keyboard.isPressed['W']) {
        y+=5;
    }
    if (engine.window.keyboard.isPressed['A']) {
        x-=5;
    }
    if (engine.window.keyboard.isPressed['S']) {
        y-=5;
    }
    if (engine.window.keyboard.isPressed['D']) {
        x+=5;
    }
    double scrollDelta = engine.window.mouse.scrollDelta;
    if (scrollDelta != 0.0f) {
        float scrollValue = scrollDelta / 100.0f;
        std::cout << "scroll: " << scrollValue << "\n";
        gameView.addZoomStep(scrollValue);
    }

    x = std::clamp<int>(x, 0, 1000);
    y = std::clamp<int>(y, 0, 700);

    game.setPlayerX(x);
    game.setPlayerY(y);
}
void GamePanel::render() {
    gameView.render();
}

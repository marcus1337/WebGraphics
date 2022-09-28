#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, GameDemo& _game) : engine(_engine), game(_game), view(_engine, _game.getMapWidth(), _game.getMapHeight()) {
}

void GameView::paintBackground() {
    Rect rect(engine);
    rect.setRadius(0.08f);
    rect.setColor({ 0.0f, 0.4f, 0.0f });
    rect.setSize(view.getWidth(), view.getHeight());
    view.paint(rect);
}

void GameView::paintPlayer() {
    Rect rect(engine);
    rect.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    rect.setSize(game.player.getDiameter(), game.player.getDiameter());
    rect.setPosition(game.player.getX() - rect.getWidth()/2, game.player.getY() - rect.getHeight()/2);
    view.paint(rect);
}

void GameView::paint() {
    view.clear();
    paintBackground();
    paintPlayer();
}

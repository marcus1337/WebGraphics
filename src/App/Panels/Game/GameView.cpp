#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, Game& _game) : engine(_engine), game(_game), view(_engine, _game.getMapWidth(), _game.getMapHeight()) {
}

/*void GameView::offsetPosition(Drawable& drawable) {
    int x = gameCamera.getXOffset(drawable.getX());
    int y = gameCamera.getYOffset(drawable.getY());
    drawable.setCenterPosition(x, y);
}

void GameView::setZoomSize(Drawable& drawable) {
    int w = drawable.getWidth();
    int h = drawable.getHeight();
    drawable.setSize(gameCamera.getZoomedWidth(w), gameCamera.getZoomedHeight(h));
}

void GameView::adjustToCameraAndPaint(Drawable& drawable) {
    setZoomSize(drawable);
    offsetPosition(drawable);
    cameraView.paint(drawable);
}*/

void GameView::paintBackground() {
    Rect rect(engine);
    rect.setRadius(0.08f);
    rect.setColor({ 0.0f, 0.4f, 0.0f });
    rect.setSize(view.getWidth(), view.getHeight());
    view.paint(rect);
}

void GameView::paintPlayer() {
    Rect playerRect(engine);
    playerRect.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    playerRect.setSize(game.getPlayerDiameter(), game.getPlayerDiameter());
    playerRect.setPosition(game.getPlayerX() - game.getPlayerRadius(), game.getPlayerY() - game.getPlayerRadius());
    view.paint(playerRect);
}

void GameView::paint() {
    view.clear();
    paintBackground();
    paintPlayer();
}

#include "GameView.h"

GameView::GameView(Engine& _engine) : Panel(_engine) {

}

void GameView::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void GameView::render() {
    renderButtons();
}
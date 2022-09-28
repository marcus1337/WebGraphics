#include "Game.h"

int Game::getPlayerX() {
    return playerX;
}
int Game::getPlayerY() {
    return playerY;
}
void Game::setPlayerX(int _x) {
    playerX = _x;
}
void Game::setPlayerY(int _y) {
    playerY = _y;
}
int Game::getMapWidth() {
    return 1200;
}
int Game::getMapHeight() {
    return 800;
}
int Game::getPlayerDiameter() {
    return 50;
}
int Game::getPlayerRadius() {
    return getPlayerDiameter() / 2;
}

void Game::setMoveAction(MoveAction moveAction) {
    playerMoveAction = moveAction;
}
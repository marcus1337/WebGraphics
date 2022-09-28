#include "GameDemo.h"
#include <algorithm>

void GameDemo::tick() {
    ticks++;
    int playerXVelocity = 0;
    int playerYVelocity = 0;

    if (playerMoveAction == MoveAction::NONE) {

    }
    if (playerMoveAction == MoveAction::LEFT) {
        playerXVelocity -= 1;
    }
    if (playerMoveAction == MoveAction::LEFT_DOWN) {
        playerXVelocity -= 1;
        playerYVelocity -= 1;
    }
    if (playerMoveAction == MoveAction::LEFT_UP) {
        playerXVelocity -= 1;
        playerYVelocity += 1;
    }
    if (playerMoveAction == MoveAction::UP) {
        playerYVelocity += 1;
    }
    if (playerMoveAction == MoveAction::DOWN) {
        playerYVelocity -= 1;
    }
    if (playerMoveAction == MoveAction::RIGHT) {
        playerXVelocity += 1;
    }
    if (playerMoveAction == MoveAction::RIGHT_DOWN) {
        playerXVelocity += 1;
        playerYVelocity -= 1;
    }
    if (playerMoveAction == MoveAction::RIGHT_UP) {
        playerXVelocity += 1;
        playerYVelocity += 1;
    }

    playerX += playerXVelocity;
    playerY += playerYVelocity;
    playerX = std::clamp<int>(playerX, 0, getMapWidth());
    playerY = std::clamp<int>(playerY, 0, getMapHeight());
}
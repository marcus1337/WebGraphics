#include "GameDemo.h"
#include <algorithm>

GameDemo::GameDemo() {
    player.setPosition(100, 100);
}

void GameDemo::tick() {
    ticks++;
    
    player.move();
    int clampedPlayerXPosition = std::clamp<int>(player.getX(), 0, getMapWidth());
    int clampedPlayerYPosition = std::clamp<int>(player.getY(), 0, getMapHeight());
    player.setPosition(clampedPlayerXPosition, clampedPlayerYPosition);
}


int GameDemo::getMapWidth() {
    return 1200;
}
int GameDemo::getMapHeight() {
    return 800;
}
#include "GameCamera.h"
#include <algorithm>

void GameCamera::addZoomStep(float _zoom) {
    if (_zoom > 0)
        zoom = zoom + 0.5f;
    if (_zoom < 0)
        zoom = zoom - 0.5f;
    zoom = std::clamp<float>(zoom, 0.5f, 5.0f);
}

void GameCamera::resetZoom() {
    zoom = 1.0f;
}

int GameCamera::getX() {
    return x;
}

int GameCamera::getY() {
    return y;
}

void GameCamera::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}

int GameCamera::getXOffset(int _x) {
    return _x - x;
}
int GameCamera::getYOffset(int _y) {
    return _y - y;
}

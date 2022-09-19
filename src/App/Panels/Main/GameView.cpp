#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, Game& _game) : engine(_engine), game(_game), view(_engine, 1920, 1080) {
}

void GameView::render() {
    int cameraWidth = 500;
    int cameraHeight = 400;
    int mapWidth = 2000;
    int mapHeight = 1000;
    int zoomAdjustedCameraWidth = (int)((float)cameraWidth * zoom);
    int zoomAdjustedCameraHeight = (int)((float)cameraHeight * zoom);
    cameraLowerLeftX = game.getPlayerX() - zoomAdjustedCameraWidth / 2;
    cameraLowerLeftY = game.getPlayerY() - zoomAdjustedCameraHeight / 2;
    cameraLowerLeftX = std::clamp(cameraLowerLeftX, 0, mapWidth - zoomAdjustedCameraWidth / 2);
    cameraLowerLeftY = std::clamp(cameraLowerLeftY, 0, mapHeight - zoomAdjustedCameraHeight / 2);

    view.clear();
    paint();
    view.render();
}

void GameView::addZoomStep(float _zoom) {
    if (_zoom > 0)
        zoom = zoom + 0.5f;
    if (_zoom < 0)
        zoom = zoom - 0.5f;
    zoom = std::clamp<float>(zoom, 0.5f, 5.0f);
}

int GameView::getXOffset(int _x) {
    return _x - cameraLowerLeftX;
}
int GameView::getYOffset(int _y) {
    return _y - cameraLowerLeftY;
}

void GameView::resetZoom() {
    zoom = 1.0f;
    view.setSize(zoom * view.getPixelWidth(), zoom * view.getPixelHeight());
}

void GameView::paint() {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 70; j++) {
            Rect rect(engine);
            int width = 100;
            int height = 100;
            int adjustedWidth = (int)((float)width * zoom);
            int adjustedHeight = (int)((float)height * zoom);
            rect.setSize(adjustedWidth, adjustedHeight);
            rect.setColor(glm::vec3(r, g, b));
            int xPos = getXOffset(i * 100*zoom);
            int yPos = getYOffset(j * 100*zoom);
            rect.setPosition((int)xPos, (int)yPos);
            rect.setRadius(0.2f);
            view.paint(rect);
            r += 0.001f;
            g = 1.0f - (1.0f * r);
            b += 0.005f;
        }
    }
}
#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, Game& _game) : engine(_engine), game(_game), view(_engine, 2000, 1500) {
    paint();
}

void GameView::render() {
    view.render();
}

void GameView::setCenterPosition(int _x, int _y) {
    view.setPosition(_x + view.getWidth() / 2, _y + view.getHeight() / 2);
}

void GameView::setZoom(float _zoom) {
    view.setSize(1.0f + _zoom, 1.0f + _zoom);
}

void GameView::paint() {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 150; j++) {
            Rect rect(engine);
            rect.setSize(100, 100);
            rect.setColor(glm::vec3(r, g, b));
            rect.setPosition(i * 100, j * 100);
            rect.setRadius(0.15f);
            view.paint(rect);
            r += 0.0001f;
            g = 1.0f - (1.0f * r);
            b += 0.0005f;
        }
    }
}
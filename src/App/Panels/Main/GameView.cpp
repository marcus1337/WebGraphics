#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, Game& _game) : engine(_engine), game(_game), view(_engine, 1000, 700) {
    paint();
}

void GameView::render() {
    view.render();
}

void GameView::setCenterPosition(int _x, int _y) {
    view.setPosition(_x + view.getWidth() / 2, _y + view.getHeight() / 2);
}

void GameView::setZoom(float _zoom) {
    zoom = _zoom;
    view.setSize((1.0f + zoom) * view.getPixelWidth(), (1.0f + zoom) * view.getPixelHeight());
}
void GameView::addZoom(float _zoom) {
    zoom += _zoom;
    view.setSize((1.0f + zoom) * view.getPixelWidth(), (1.0f + zoom) * view.getPixelHeight());
}
void GameView::resetZoom() {
    setZoom(0.0f);
}

void GameView::paint() {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 70; j++) {
            Rect rect(engine);
            rect.setSize(100, 100);
            rect.setColor(glm::vec3(r, g, b));
            rect.setPosition(i * 100, j * 100);
            rect.setRadius(0.2f);
            view.paint(rect);
            r += 0.001f;
            g = 1.0f - (1.0f * r);
            b += 0.005f;
        }
    }
}
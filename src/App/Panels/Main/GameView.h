#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Drawables/View.h>

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView {

    Engine& engine;
    Game& game;
    View view;

    void paint();
    float zoom = 1.0f;
public:
    GameView(Engine& _engine, Game& _game);
    void render();

    void addZoomStep(float _zoom);
    void resetZoom();

};

#endif

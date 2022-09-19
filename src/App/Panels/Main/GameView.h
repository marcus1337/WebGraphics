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
    float zoom = 0.0f;
public:
    GameView(Engine& _engine, Game& _game);
    void render();

    void setCenterPosition(int _x, int _y);
    void setZoom(float _zoom);
    void addZoom(float _zoom);
    void resetZoom();

};

#endif

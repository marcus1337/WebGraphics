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

public:
    GameView(Engine& _engine, Game& _game);
    void render();

    void setCenterPosition(int _x, int _y);
    void setZoom(float _zoom); //0...1

};

#endif

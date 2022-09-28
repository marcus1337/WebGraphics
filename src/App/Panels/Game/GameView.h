#include <Engine/Engine.h>
#include <Game/GameDemo.h>
#include <Drawables/View.h>
#include "GameCamera.h"

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView {

    Engine& engine;
    GameDemo& game;
    
    void paintBackground();
    void paintPlayer();
public:
    GameView(Engine& _engine, GameDemo& _game);
    void paint();
    View view;
};

#endif

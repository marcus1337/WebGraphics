#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Drawables/View.h>
#include "GameCamera.h"

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView {

    Engine& engine;
    Game& game;

    //GameCamera& gameCamera;
    //void offsetPosition(Drawable& drawable);
    //void setZoomSize(Drawable& drawable);
    //void adjustToCameraAndPaint(Drawable& drawable);
    
    void paintBackground();
    void paintPlayer();
public:
    GameView(Engine& _engine, Game& _game);
    void paint();
    View view;
};

#endif

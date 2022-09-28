#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Drawables/View.h>
#include "GameCamera.h"

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {

    Engine& engine;
    Game& game;
    GameCamera& gameCamera;

public:
    GameController(Engine& _engine, Game& _game, GameCamera& _gameCamera);
    void update();

};

#endif // !GAMECONTROLLER_H

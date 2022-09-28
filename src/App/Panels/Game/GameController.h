#include <Engine/Engine.h>
#include <Game/GameDemo.h>
#include <Drawables/View.h>
#include "GameCamera.h"

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {

    Engine& engine;
    GameDemo& game;
    GameCamera& gameCamera;
    Keyboard& keyboard;
    Mouse& mouse;

    MoveAction getMoveAction();

public:
    GameController(Engine& _engine, GameDemo& _game, GameCamera& _gameCamera);
    void update();

};

#endif // !GAMECONTROLLER_H

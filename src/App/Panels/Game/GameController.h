#include <Engine/Engine.h>
#include <Game/GameDemo.h>
#include <Drawables/View.h>

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController {

    Engine& engine;
    GameDemo& game;
    Keyboard& keyboard;
    Mouse& mouse;

    MoveAction getMoveAction();

public:
    GameController(Engine& _engine, GameDemo& _game);
    void update();

};

#endif // !GAMECONTROLLER_H

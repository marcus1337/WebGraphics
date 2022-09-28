#include "GameController.h"

GameController::GameController(Engine& _engine, GameDemo& _game, GameCamera& _gameCamera) : engine(_engine), game(_game), gameCamera(_gameCamera), keyboard(_engine.window.keyboard), mouse(_engine.window.mouse) {

}

MoveAction GameController::getMoveAction() {
    bool up = keyboard.isPressed['W'];
    bool down = keyboard.isPressed['S'];
    bool left = keyboard.isPressed['A'];
    bool right = keyboard.isPressed['D'];
    if (up && left)
        return MoveAction::LEFT_UP;
    if (down && left)
        return MoveAction::LEFT_DOWN;
    if (up && right)
        return MoveAction::RIGHT_UP;
    if (down && right)
        return MoveAction::RIGHT_DOWN;
    if (left)
        return MoveAction::LEFT;
    if (right)
        return MoveAction::RIGHT;
    if (up)
        return MoveAction::UP;
    if (down)
        return MoveAction::DOWN;
    return MoveAction::NONE;
}

void GameController::update() {
    game.player.setMoveAction(getMoveAction());
}
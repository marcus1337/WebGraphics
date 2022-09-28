#include "GameController.h"

GameController::GameController(Engine& _engine, Game& _game, GameCamera& _gameCamera) : engine(_engine), game(_game), gameCamera(_gameCamera) {

}

void GameController::update() {
    if (engine.window.keyboard.isPressed['W']) {
        game.setMoveAction(MoveAction::UP);
    }
    if (engine.window.keyboard.isPressed['A']) {
        game.setMoveAction(MoveAction::LEFT);
    }
    if (engine.window.keyboard.isPressed['S']) {
        game.setMoveAction(MoveAction::DOWN);
    }
    if (engine.window.keyboard.isPressed['D']) {
        game.setMoveAction(MoveAction::RIGHT);
    }
}
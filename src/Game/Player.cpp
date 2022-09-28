
#include "Player.h"

void Player::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}
int Player::getX() {
    return x;
}
int Player::getY() {
    return y;
}
int Player::getRadius() {
    return 25;
}
int Player::getDiameter() {
    return getRadius() * 2;
}
void Player::setMoveAction(MoveAction _moveAction) {
    moveAction = _moveAction;
}

void Player::setVelocity() {
    xVelocity = 0;
    yVelocity = 0;

    switch (moveAction) {
    case MoveAction::NONE:
        break;
    case MoveAction::LEFT:
        xVelocity -= 2;
        break;
    case MoveAction::UP:
        yVelocity += 2;
        break;
    case MoveAction::DOWN:
        yVelocity -= 2;
        break;
    case MoveAction::RIGHT:
        xVelocity += 2;
        break;
    case MoveAction::LEFT_UP:
        xVelocity -= 2;
        yVelocity += 2;
        break;
    case MoveAction::LEFT_DOWN:
        xVelocity -= 2;
        yVelocity -= 2;
        break;
    case MoveAction::RIGHT_UP:
        xVelocity += 2;
        yVelocity += 2;
        break;
    case MoveAction::RIGHT_DOWN:
        xVelocity += 2;
        yVelocity -= 2;
        break;
    default:
        break;
    };
}

void Player::move() {
    setVelocity();
    x += xVelocity;
    y += yVelocity;
}




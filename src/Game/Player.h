#include "Action.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {

    int x = 0;
    int y = 0;
    int xVelocity = 0;
    int yVelocity = 0;
    MoveAction moveAction;
    void setVelocity();
public:

    void setPosition(int x, int y);
    int getX();
    int getY();
    int getRadius();
    int getDiameter();
    void setMoveAction(MoveAction moveAction);
    void move();

};

#endif
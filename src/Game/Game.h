#include <stdint.h>

#ifndef GAME_H
#define GAME_H

enum class MoveAction {
    NONE = 0, LEFT, LEFT_UP, LEFT_DOWN, UP, DOWN, RIGHT, RIGHT_UP, RIGHT_DOWN
};

class Game {

protected:

    uint64_t ticks = 0;
    int playerX = 0;
    int playerY = 0;
    MoveAction playerMoveAction = MoveAction::NONE;

public:

    virtual ~Game() = default;
    virtual void tick() = 0;
    
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int _x);
    void setPlayerY(int _y);
    void setMoveAction(MoveAction moveAction);

    int getPlayerDiameter();
    int getPlayerRadius();
    int getMapWidth();
    int getMapHeight();
};

#endif // !GAME_H

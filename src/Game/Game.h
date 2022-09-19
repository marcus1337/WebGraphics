#include <stdint.h>

#ifndef GAME_H
#define GAME_H

class Game {

protected:

    uint64_t ticks = 0;
    int x = 0;
    int y = 0;

public:

    virtual ~Game() = default;
    virtual void tick() = 0;
    
    int getPlayerX();
    int getPlayerY();
    void setPlayerX(int _x);
    void setPlayerY(int _y);
};

#endif // !GAME_H

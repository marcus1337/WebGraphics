#include <stdint.h>

#ifndef GAME_H
#define GAME_H
class Game {

protected:
    uint64_t ticks = 0;

public:

    virtual ~Game() = default;
    virtual void tick() = 0;
   
};

#endif // !GAME_H

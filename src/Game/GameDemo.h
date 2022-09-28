#include "Game.h"
#include "Action.h"
#include "Player.h"

#ifndef GAMEDEMO_H
#define GAMEDEMO_H

class GameDemo : public Game {

public:
    GameDemo();
    Player player;
    virtual void tick() override;
    int getMapWidth();
    int getMapHeight();

};

#endif // !GAMEDEMO_H

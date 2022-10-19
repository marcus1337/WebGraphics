#include <stdint.h>
#include "Board.h"

#ifndef CHESS_H
#define CHESS_H
class Chess {

protected:
    int turn = 0;

public:

    Board board;
    int getTurn();
   
};

#endif // !GAME_H

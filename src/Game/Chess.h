#include <stdint.h>
#include "Board/Board.h"

#ifndef CHESS_H
#define CHESS_H
class Chess {

protected:
    int turn = 0;

public:

    Board board;
    int getTurn();
    PieceColor getPlayerTurn();

    bool isDraw();
    bool isCheckMate();
   
};

#endif // !GAME_H

#include "TicTacToe.h"

#ifndef AI_H
#define AI_H

class AI {

    bool isWinnablePlacement(int row, int col, TicTacToe& ticTacToe);
    bool tryPlaceWinnableMark(TicTacToe& ticTacToe);
    void placeAnyMark(TicTacToe& ticTacToe);

public:

    void placeMark(TicTacToe& ticTacToe);

};

#endif

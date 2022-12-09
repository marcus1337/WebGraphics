#include <stdint.h>
#include "Board.h"
#include <vector>

#ifndef TICTACTOE_H
#define TICTACTOE_H
class TicTacToe {

protected:
    Board board;
    Tile getWinner(std::array<Tile, 3> tileLine);

public:
    TicTacToe();
    void reset();
    int getTurn();
    Tile getTurnMark();

    bool isDraw();
    Tile getWinner();
    bool isGameOver();
    Tile getTile(int row, int col);
    void setTile(int row, int col);
    
};

#endif // !GAME_H

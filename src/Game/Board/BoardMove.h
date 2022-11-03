#include "BoardCheck.h"

#ifndef BOARDMOVE_H
#define BOARDMOVE_H

class BoardMove {

    Board board;
    BoardCheck boardCheck;
    PieceColor moveColor;

public:

    BoardMove(Board _board, PieceColor _moveColor);
    std::vector<Point> getMoves(Point from);
    std::vector<Point> getPawnMoves(Point from);

};

#endif
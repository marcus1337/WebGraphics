#include "BoardCheck.h"

#ifndef BOARDMOVE_H
#define BOARDMOVE_H

class BoardMove {

    Board board;
    BoardCheck boardCheck;
    PieceColor moveColor;

    std::vector<Point> getUnverifiedMoves(Point from);
    std::vector<Point> getPawnMoves(Point from);
    std::vector<Point> getOtherMoves(Point from);

    bool canPawnTake(Point to, PieceColor pawnColor);
    bool canPawnPassantTake(Point to, PieceColor pawnColor);
    bool canPawnNormalTake(Point to, PieceColor pawnColor);
    bool canPawnTwoStep(Point from);

    bool isMoveCausingSelfCheck(Point from, Point to);

public:

    BoardMove(Board _board, PieceColor _moveColor);
    std::vector<Point> getMoves(Point from);
    bool canMove();

};

#endif
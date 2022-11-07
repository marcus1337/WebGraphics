#include "BoardCheck.h"

#ifndef BOARDMOVE_H
#define BOARDMOVE_H

class BoardMove {

    Board board;
    BoardCheck boardCheck;
    PieceColor moveColor;

    std::vector<Point> getUnverifiedMoves(Point from);
    std::vector<Point> getPawnMoves(Point from);
    std::vector<Point> getPawnNormalMoves(Point from);
    std::vector<Point> getPawnAttackMoves(Point from);
    bool isPawnPromoteMove(Point to);
    std::vector<Point> getPawnPromoteMoves(Point to);
    std::vector<Point> getKingMoves(Point from);
    std::vector<Point> getOtherMoves(Point from);

    bool canPawnTake(Point to);
    bool canPawnPassantTake(Point to);
    bool canPawnNormalTake(Point to);
    bool canPawnTwoStep(Point from);

    bool isMoveCausingSelfCheck(Point from, Point to);

public:

    BoardMove(Board _board, PieceColor _moveColor);
    std::vector<Point> getMoves(Point from);
    bool canMove();

};

#endif
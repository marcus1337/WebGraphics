#include <stdint.h>
#include "Board/Board.h"
#include "Board/Point.h"
#include "Board/BoardCheck.h"
#include "Board/BoardMove.h"

#ifndef CHESS_H
#define CHESS_H
class Chess {

protected:
    int turn = 0;
    Board board;
    BoardMove boardMove;
    BoardCheck boardCheck;
    PieceColor getTurnColor();
    void setBoardChecks();

public:

    Chess();
    void reset();
    void print();

    int getTurn();
    bool isWhiteTurn();
    bool isBlackTurn();

    bool isDraw();
    bool isCheckMate();
    bool isCheck();

    bool canCastleQueenSide();
    bool canCastleKingSide();
    void castleQueenSide();
    void castleKingSide();

    void move(Point from, Point to);
    std::vector<Point> getMoves(Point from);
    bool isOccupied(Point tilePosition);
    Piece getPiece(Point tilePosition);
    
};

#endif // !GAME_H

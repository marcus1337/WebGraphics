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
    void setBoardChecks();

public:

    Chess();
    void reset();
    void print();

    int getTurn();
    PieceColor getTurnColor();

    bool isDraw();
    bool isCheckMate();
    bool isCheck();

    void move(Point from, Point to);
    std::vector<Point> getMoves(Point from);
    std::vector<Point> getHumanMoves(Point from);
    bool isPromoteMove(Point from, Point to);
    void promote(Point from, Point to, PieceType promoteType);

    Tile getTile(Point point);
    
};

#endif // !GAME_H

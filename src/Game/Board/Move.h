#include "Piece.h"
#include "Point.h"
#include "Board.h"

#ifndef MOVE_H
#define MOVE_H

class Move {

    void setCastleState(Board& board);
    void setPassantState(Board& board);
    void movePassant(Board& board);
    void movePromote(Board& board);
    void moveNormal(Board& board);
    bool toTileOccupied;
    Point getPassantTakePoint();

public:

    Point from, to;
    Piece piece;

    Move(Point _from, Point _to, Board& board);

    Piece getPromotePiece();
    bool isPromote();
    bool isPassant();
    bool isCastleKingSide();
    bool isCastleQueenSide();
    Point getPromotePoint();
    int getPromoteRank();

    void apply(Board& board);

};

#endif

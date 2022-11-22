#include "Piece.h"
#include "Point.h"

#ifndef MOVE_H
#define MOVE_H

struct Move {
    Point from, to;
    Piece piece;

    Piece getPromotePiece();
    bool isPromote();
    bool isPassant(bool toTileOccupied);
    bool isCastleKingSide();
    bool isCastleQueenSide();
    Point getPromotePoint();
    int getPromoteRank();

};

#endif

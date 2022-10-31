#include "Piece.h"

#ifndef CASTLE_H
#define CASTLE_H

class Castle {
    bool kingMoved = false;
    bool queenSideRookMoved = false;
    bool kingSideRookMoved = false;

public:
    bool isKingMoved();
    bool isQueenSideRookMoved();
    bool isKingSideRookMoved();
    void setKingMoved();
    void setKingSideRookMoved();
    void setQueenSideRookMoved();

};

#endif
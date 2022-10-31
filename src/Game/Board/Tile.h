#include "Piece.h"
#include "Point.h"
#include <vector>
#include <string>

#ifndef TILE_H
#define TILE_H

class Tile {
    Piece piece;
    bool occupied = false;
public:
    std::string toString();
    Piece getPiece();
    void setPiece(Piece _piece);
    bool isOccupied();
    void setOccupied(bool _occupied);
};

#endif 

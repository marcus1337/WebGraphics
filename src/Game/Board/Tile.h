#include "Piece.h"
#include "Point.h"
#include <vector>

#ifndef TILE_H
#define TILE_H

struct Tile {
    Piece piece;
    bool occupied = false;
    std::string toString();
};

#endif 

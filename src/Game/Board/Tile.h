#include "Piece.h"
#include "Point.h"
#include "Game/Moves/Move.h"
#include <vector>

#ifndef TILE_H
#define TILE_H

struct Tile {

    Piece piece;
    bool occupied = false;
    bool movedPiece = false;
    bool passantPawn = false;
 
    std::string toString();

};

#endif 

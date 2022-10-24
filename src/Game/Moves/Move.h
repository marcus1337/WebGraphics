
#include "Game/Board/Piece.h"
#include "Game/Board/Point.h"

#ifndef MOVE_H
#define MOVE_H

struct Move {

    Point from, to;
    Piece piece;

};

#endif
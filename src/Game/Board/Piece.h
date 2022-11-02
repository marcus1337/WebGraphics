#include <vector>
#include <string>
#include "Point.h"

#ifndef PIECE_H
#define PIECE_H

enum class PieceColor {
    WHITE = 0, BLACK
};

enum class PieceType {
    PAWN = 0, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

struct Piece {
    PieceType type;
    PieceColor color;
    std::string toString();
    std::vector<Point> getNormalMoves();
    static std::vector<Point> getPawnNormalAttacks(PieceColor _color);
};



#endif
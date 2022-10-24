
#include "Game/Board/Piece.h"
#include "Game/Board/Board.h"

#ifndef MOVE_H
#define MOVE_H

enum class MoveType {
    W_PAWN, B_PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, QUEENSIDE_CASTLE_KING, KINGSIDE_CASTLE_KING, QUEENSIDE_CASTLE_ROOK, KINGSIDE_CASTLE_ROOK
};

struct Move {

    char fromFile, fromRank;
    char toFile, toRank;
    Piece piece;
    PieceColor color;

    void execute(Board& board);

};

#endif
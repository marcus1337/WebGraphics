#include "Move.h"

void Move::execute(Board& board) {
    board.setPiece(toFile, toRank, piece, color);
    board.clearTile(fromFile, fromRank);
}
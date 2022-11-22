#include "History.h"

void History::add(Move move) {
    moves.push_back(move);
}

Move History::getLastMove() {
    if (moves.empty())
        return Move();
    return moves[moves.size() - 1];
}
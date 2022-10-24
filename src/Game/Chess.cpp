#include "Chess.h"

int Chess::getTurn() {
    return turn;
}

PieceColor Chess::getPlayerTurn() {
    if (turn % 2 != 0)
        return PieceColor::BLACK;
    return PieceColor::WHITE;
}

bool isDraw() {
    return false;
}
bool isCheckMate() {
    return false;
}
#include "Tile.h"

std::string Tile::toString() {
    std::string str = "None";
    if (isOccupied())
        str = piece.toString();
    return str;
}

Piece Tile::getPiece() {
    return piece;
}

void Tile::setPiece(Piece _piece) {
    piece = _piece;
}

bool Tile::isOccupied() {
    return occupied;
}

void Tile::setOccupied(bool _occupied) {
    occupied = _occupied;
}

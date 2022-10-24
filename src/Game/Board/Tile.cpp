#include "Tile.h"

std::string Tile::toString() {
    std::string str = "None";
    if (occupied)
        str = piece.toString();
    return str;
}
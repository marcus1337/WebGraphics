#include <array>


#ifndef BOARD_H
#define BOARD_H

enum class Tile {
    EMPTY = 0, CIRCLE, CROSS
};

class Board {
    std::array<Tile, 9> tiles;
    int getTileIndex(int row, int col) const;

    std::array<std::array<Tile, 3>, 3> getVerticalLines();
    std::array<std::array<Tile, 3>, 3> getHorizontalLines();
    std::array<std::array<Tile, 3>, 2> getDiagonalLines();
public:
    Board();
    void reset();
    void setTile(int row, int col, Tile tile);
    Tile getTile(int row, int col);
    int getNumOccupiedTiles();
    std::array<std::array<Tile, 3>, 8> getLines();
};

#endif

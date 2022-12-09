#include "Board.h"
#include <algorithm>
#include <iostream>

Board::Board() : tiles{ Tile::EMPTY } {

}

int Board::getNumOccupiedTiles() {
    return std::count_if(tiles.begin(), tiles.end(), [](Tile tile) {return tile != Tile::EMPTY; });
}

void Board::reset() {
    tiles = std::array<Tile, 9>{Tile::EMPTY};
}

int Board::getTileIndex(int row, int col) const {
    return col + row * 3;
}

void Board::setTile(int row, int col, Tile tile) {
    tiles[getTileIndex(row, col)] = tile;
}

Tile Board::getTile(int row, int col) {
    return tiles[getTileIndex(row, col)];
}

std::array<std::array<Tile, 3>, 3> Board::getVerticalLines() {
    std::array<std::array<Tile, 3>, 3> lines{};
    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            lines[col][row] = getTile(row, col);
        }
    }
    return lines;
}

std::array<std::array<Tile, 3>, 3> Board::getHorizontalLines() {
    std::array<std::array<Tile, 3>, 3> lines{};
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            lines[row][col] = getTile(row, col);
        }
    }
    return lines;
}

std::array<std::array<Tile, 3>, 2> Board::getDiagonalLines() {
    std::array<std::array<Tile, 3>, 2> lines{};
    for (int row = 0, col = 0; row < 3; row++, col++) {
        lines[0][row] = getTile(row, col);
        lines[1][row] = getTile(2 - row, col);
    }
    return lines;
}

std::array<std::array<Tile, 3>, 8> Board::getLines() {
    std::array<std::array<Tile, 3>, 8> lines{};

    auto verticalLines = getVerticalLines();
    auto horizontalLines = getHorizontalLines();
    auto diagonalLines = getDiagonalLines();

    std::copy(verticalLines.begin(), verticalLines.end(), lines.begin());
    std::copy(horizontalLines.begin(), horizontalLines.end(), lines.begin() + verticalLines.size());
    std::copy(diagonalLines.begin(), diagonalLines.end(), lines.begin() + verticalLines.size() + horizontalLines.size());

    return lines;
}
#include "TicTacToe.h"
#include <iostream>

TicTacToe::TicTacToe() {

}

void TicTacToe::reset() {
    board.reset();
}

int TicTacToe::getTurn() {
    return board.getNumOccupiedTiles();
}

bool TicTacToe::isDraw() {
    return getTurn() == 9 && getWinner() == Tile::EMPTY;
}

Tile TicTacToe::getWinner(std::array<Tile, 3> line) {
    if (line[0] == line[1] && line[1] == line[2])
        return line[0];
    return Tile::EMPTY();
}

Tile TicTacToe::getWinner() {
    for (auto line : board.getLines())
        if (getWinner(line) != Tile::EMPTY)
            return getWinner(line);
    return Tile::EMPTY();
}

bool TicTacToe::isGameOver() {
    return getWinner() != Tile::EMPTY || isDraw();
}

Tile TicTacToe::getTile(int row, int col) {
    return board.getTile(row, col);
}

void TicTacToe::setTile(int row, int col) {
    Tile tile = Tile::CIRCLE;
    if (getTurn() % 2 != 0)
        tile = Tile::CROSS;
    board.setTile(row, col, tile);
}



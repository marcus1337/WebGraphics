#include "AI.h"

void AI::placeMark(TicTacToe& ticTacToe) {
    if (tryPlaceWinnableMark(ticTacToe))
        return;
    placeAnyMark(ticTacToe);
}

bool AI::tryPlaceWinnableMark(TicTacToe& ticTacToe) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (isWinnablePlacement(row, col, ticTacToe)) {
                ticTacToe.setTile(row, col);
                return true;
            }
        }
    }
    return false;
}

void AI::placeAnyMark(TicTacToe& ticTacToe) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (ticTacToe.getTile(row, col) == Tile::EMPTY) {
                ticTacToe.setTile(row, col);
                return;
            }
        }
    }
}

bool AI::isWinnablePlacement(int row, int col, TicTacToe& ticTacToe) {
    TicTacToe ticTacToeCopy = ticTacToe;
    if (ticTacToeCopy.getTile(row, col) == Tile::EMPTY) {
        ticTacToeCopy.setTile(row, col);
        if (ticTacToeCopy.isGameOver())
            return true;
    }
    return false;
}
#include "Chess.h"
#include <iostream>

Chess::Chess() : board(), boardCheck(board, PieceColor::WHITE), boardMove(board, PieceColor::WHITE) {

}

void Chess::print() {
    board.print();
    std::cout << "-------------\n";
    boardCheck.print();
}

void Chess::setBoardChecks() {
    boardCheck = BoardCheck(board, getTurnColor());
    boardMove = BoardMove(board, getTurnColor());
}

PieceColor Chess::getTurnColor() {
    if (getTurn() % 2 == 0)
        return PieceColor::WHITE;
    else
        return PieceColor::BLACK;
}

void Chess::reset() {
    turn = 0;
    board.reset();
    setBoardChecks();
}

int Chess::getTurn() {
    return turn;
}

bool Chess::isDraw() {
    return !boardCheck.isKingChecked() && !boardMove.canMove();
}

bool Chess::isCheckMate() {
    return boardCheck.isKingChecked() && !boardMove.canMove();
}

bool Chess::isCheck() {
    return boardCheck.isKingChecked();
}

void Chess::move(Point from, Point to) {
    board.movePiece(from, to);
    turn++;
    setBoardChecks();
    print();
}

std::vector<Point> Chess::getMoves(Point from) {
    return boardMove.getMoves(from);
}

Tile Chess::getTile(Point point) {
    return board.getTile(point);
}


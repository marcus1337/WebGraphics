#include "Chess.h"

Chess::Chess() : board(), boardCheck(board, PieceColor::WHITE), boardMove(board, PieceColor::WHITE) {

}

void Chess::print() {
    board.print();
}

void Chess::setBoardChecks() {
    boardCheck = BoardCheck(board, getTurnColor());
    boardMove = BoardMove(board, getTurnColor());
}

PieceColor Chess::getTurnColor() {
    if (isWhiteTurn())
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

bool Chess::isWhiteTurn() {
    return getTurn() % 2 == 0;
}
bool Chess::isBlackTurn() {
    return !isWhiteTurn();
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

bool Chess::canCastleQueenSide() {
    return boardCheck.canQueenSideCastle();
}

bool Chess::canCastleKingSide() {
    return boardCheck.canKingSideCastle();
}

void Chess::castleQueenSide() {
    board.castleQueenSide(getTurnColor());
}

void Chess::castleKingSide() {
    board.castleKingSide(getTurnColor());
}

void Chess::move(Point from, Point to) {
    board.movePiece(from, to);
    turn++;
}

std::vector<Point> Chess::getMoves(Point from) {
    return boardMove.getMoves(from);
}

bool Chess::isOccupied(Point tilePosition) {
    return board.getTile(tilePosition).isOccupied();
}

Piece Chess::getPiece(Point tilePosition) {
    return board.getTile(tilePosition).getPiece();
}


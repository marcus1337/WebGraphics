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
    Move move = getMove(from, to);
    history.add(move);
    move.apply(board);
    turn++;
    setBoardChecks();
}

std::vector<Point> Chess::getMoves(Point from) {
    return boardMove.getMoves(from);
}

Tile Chess::getTile(Point point) {
    return board.getTile(point);
}

std::vector<Point> Chess::getHumanMoves(Point from) {
    auto moves = getMoves(from);
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].rank < 0)
            moves[i].rank = 0;
        if (moves[i].rank > 7)
            moves[i].rank = 7;
    }
    return moves;
}

bool Chess::isPromoteMove(Point from, Point to) {
    Move move(from, to, board);
    return move.isPromote();
}

void Chess::promote(Point from, Point to, PieceType promoteType) {
    if (to.rank == 7)
        to.rank += (int)promoteType;
    else
        to.rank -= (int)promoteType;
    move(from, to);
}

Move Chess::getMove(Point from, Point to) {
    return Move(from, to, board);
}
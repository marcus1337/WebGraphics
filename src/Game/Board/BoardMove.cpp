#include "BoardMove.h"

BoardMove::BoardMove(Board _board, PieceColor _moveColor) : board(_board), moveColor(_moveColor), boardCheck(_board, _moveColor) {

}

bool BoardMove::canKingSideCastle() {
    return false;
}
bool BoardMove::canQueenSideCastle() {
    return false;
}
std::vector<Point> BoardMove::getMoves(Point from) {
    if (!board.getTile(from).isOccupied())
        return {};
    Piece piece = board.getTile(from).getPiece();
    if (piece.type == PieceType::PAWN)
        return getPawnMoves(from);

    std::vector<Point> points;
    return points;
}

std::vector<Point> BoardMove::getPawnMoves(Point from) {
    std::vector<Point> points;


    return points;
}


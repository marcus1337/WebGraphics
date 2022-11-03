#include "BoardMove.h"

BoardMove::BoardMove(Board _board, PieceColor _moveColor) : board(_board), moveColor(_moveColor), boardCheck(_board, _moveColor) {

}

std::vector<Point> BoardMove::getUnverifiedMoves(Point from) {
    if (!board.getTile(from).isOccupied())
        return {};
    Piece piece = board.getTile(from).getPiece();
    if (piece.type == PieceType::PAWN)
        return getPawnMoves(from);
    else
        return getOtherMoves(from);
}

std::vector<Point> BoardMove::getMoves(Point from) {
    std::vector<Point> verifiedMoves;
    for (Point to : getUnverifiedMoves(from)) {
        if (!isMoveCausingSelfCheck(from, to))
            verifiedMoves.push_back(to);
    }
    return verifiedMoves;
}

bool BoardMove::isMoveCausingSelfCheck(Point from, Point to) {
    Board boardCopy = board;
    boardCopy.movePiece(from, to);
    BoardCheck boardCopyCheck(boardCopy, moveColor);
    return boardCopyCheck.isKingChecked();
}

std::vector<Point> BoardMove::getPawnMoves(Point from) {
    std::vector<Point> points;


    return points;
}

std::vector<Point> BoardMove::getOtherMoves(Point from) {
    Piece piece = board.getTile(from).getPiece();
    std::vector<Point> moves;
    for (Point point : piece.getNormalMoves()) {
        Point moveTo = from + point;
        if(moveTo.isInsideBoard())
            moves.push_back(moveTo);
    }
    return moves;
}



#include "BoardCheck.h"

BoardCheck::BoardCheck(Board _board, PieceColor _checkColor) : board(_board), checkColor(_checkColor) {

}

void BoardCheck::clearChecks() {
    checks = std::array<std::array<bool, 8>, 8>{false};
}

bool BoardCheck::isPlaceableTile(Point toPoint) {
    bool insideBoard = toPoint.file >= 0 && toPoint.file <= 7 && toPoint.rank >= 0 && toPoint.rank <= 7;
    if (!insideBoard)
        return false;
    Tile tile = board.getTile(toPoint.file, toPoint.rank);
    return !tile.isOccupied() || tile.getPiece().color != checkColor;
}

void BoardCheck::setChecks() {
    clearChecks();
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            Tile tile = board.getTile(file, rank);
            if (tile.isOccupied() && tile.getPiece().color == checkColor) {
                setChecks(Point{ file, rank }, tile.getPiece());
            }
        }
    }
}
bool BoardCheck::isChecked(Point point) {
    return checks[point.file][point.rank];
}

void BoardCheck::setChecks(Point fromPoint, Piece piece) {
    if (piece.type == PieceType::PAWN)
        setPawnChecks(fromPoint);
    if (piece.type == PieceType::KING)
        setKingChecks(fromPoint);
    if (piece.type == PieceType::KNIGHT)
        setKnightChecks(fromPoint);
    if (piece.type == PieceType::BISHOP)
        setDiagonalChecks(fromPoint);
    if (piece.type == PieceType::ROOK)
        setStraightChecks(fromPoint);
    if (piece.type == PieceType::QUEEN) {
        setDiagonalChecks(fromPoint);
        setStraightChecks(fromPoint);
    }
}

void BoardCheck::setPawnChecks(Point fromPoint) {

}

void BoardCheck::setKnightChecks(Point fromPoint) {

}

void BoardCheck::setDiagonalChecks(Point fromPoint) {

}

void BoardCheck::setStraightChecks(Point fromPoint) {

}

void BoardCheck::setKingChecks(Point fromPoint) {

}




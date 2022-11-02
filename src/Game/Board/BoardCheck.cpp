#include "BoardCheck.h"

BoardCheck::BoardCheck(Board _board, PieceColor _checkColor) : board(_board), checkColor(_checkColor), checks{false} {
    setChecks();
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

void BoardCheck::setChecks(Point from, Piece piece) {
    std::vector<Point> points = piece.getNormalMoves();
    for (Point point : points) {
        Point to = point + from;
        if (isPlaceableTile(to))
            checks[to.file][to.rank] = true;
    }
}






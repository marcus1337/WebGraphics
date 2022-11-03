#include "BoardCheck.h"

BoardCheck::BoardCheck(Board _board, PieceColor _checkColor) : board(_board), checkColor(_checkColor), checks{ false } {
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
bool BoardCheck::isPointChecked(Point point) {
    return checks[point.file][point.rank];
}

bool BoardCheck::isPathBlocked(Point from, Point to, Piece piece) {
    if (!isBlockablePiece(piece))
        return false;
    while (from != to) {
        from.closeDistance(to);
        if (from != to && board.getTile(from).isOccupied())
            return true;
    }
    return false;
}

bool BoardCheck::isBlockablePiece(Piece piece) {
    return piece.type == PieceType::BISHOP || piece.type == PieceType::QUEEN || piece.type == PieceType::ROOK;
}

void BoardCheck::setChecks(Point from, Piece piece) {
    std::vector<Point> points = piece.getNormalMoves();
    if (piece.type == PieceType::PAWN)
        points = Piece::getPawnNormalAttacks(piece.color);
    for (Point point : points) {
        Point to = point + from;
        if (isPlaceableTile(to))
            checks[to.file][to.rank] = !isPathBlocked(from, to, piece);
    }
}

bool BoardCheck::isKingChecked() {
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            Tile tile = board.getTile(file, rank);
            Piece piece = tile.getPiece();
            if (tile.isOccupied() && piece.color == checkColor && piece.type == PieceType::KING) {
                return checks[file][rank];
            }
        }
    }
    return false;
}

bool BoardCheck::canKingSideCastle() {
    Castle& castle = checkColor == PieceColor::WHITE ? board.whiteCastle : board.blackCastle;
    int rank = checkColor == PieceColor::WHITE ? 0 : 7;
    for (int file = 4; file < 7; file++)
        if (isPointChecked(Point{ file, rank }))
            return false;
    return !castle.isKingMoved() && !castle.isKingSideRookMoved();
}

bool BoardCheck::canQueenSideCastle() {
    Castle& castle = checkColor == PieceColor::WHITE ? board.whiteCastle : board.blackCastle;
    int rank = checkColor == PieceColor::WHITE ? 0 : 7;
    for (int file = 4; file >= 2; file--)
        if (isPointChecked(Point{ file, rank }))
            return false;
    return !castle.isKingMoved() && !castle.isQueenSideRookMoved();
}





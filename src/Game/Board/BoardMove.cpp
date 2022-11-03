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

bool BoardMove::canPawnTake(Point to, PieceColor pawnColor) {
    return canPawnNormalTake(to, pawnColor) || canPawnPassantTake(to, pawnColor);
}

bool BoardMove::canPawnPassantTake(Point to, PieceColor pawnColor) {
    int passantRank = pawnColor == PieceColor::WHITE ? 5 : 2;
    EnPassant& passant = pawnColor == PieceColor::WHITE ? board.whitePassant : board.blackPassant;
    if (!passant.isPawnTwoStepped())
        return false;
    if (to.file != passant.getTwoSteppedPawnFile())
        return false;
    return to.rank == passantRank;
}

bool BoardMove::canPawnNormalTake(Point to, PieceColor pawnColor) {
    Tile tile = board.getTile(to);
    return tile.isOccupied() && tile.getPiece().color != pawnColor;
}

std::vector<Point> BoardMove::getPawnMoves(Point from) {
    Piece piece = board.getTile(from).getPiece();
    PieceColor color = piece.color;
    std::vector<Point> moves;
    for (Point point : Piece::getPawnNormalAttacks(color)) {
        Point moveTo = point + from;
        if (moveTo.isInsideBoard() && canPawnTake(moveTo, color))
            moves.push_back(moveTo);
    }
    if (canPawnTwoStep(from)) {
        int rankDiff = color == PieceColor::WHITE ? 2 : -2;
        moves.push_back(from + Point{ 0, rankDiff });
    }

    for (Point point : piece.getNormalMoves()) {
        Point move = point + from;
        if (!board.getTile(move).isOccupied()) {
            int promoteRank = color == PieceColor::WHITE ? 7 : 0;
            int knightPromoteRank = color == PieceColor::WHITE ? 8 : -1;
            int bishopPromoteRank = color == PieceColor::WHITE ? 9 : -2;
            int rookPromoteRank = color == PieceColor::WHITE ? 10 : -3;
            int queenPromoteRank = color == PieceColor::WHITE ? 11 : -4;
            if (move.rank == promoteRank) {
                moves.push_back(Point{ move.file, knightPromoteRank });
                moves.push_back(Point{ move.file, bishopPromoteRank });
                moves.push_back(Point{ move.file, rookPromoteRank });
                moves.push_back(Point{ move.file, queenPromoteRank });
            }
            else
                moves.push_back(move);
        }
    }
    return moves;
}

bool BoardMove::canPawnTwoStep(Point from) {
    PieceColor color = board.getTile(from).getPiece().color;
    int startRank = color == PieceColor::WHITE ? 1 : 6;
    int middleRank = color == PieceColor::WHITE ? 2 : 5;
    int toRank = color == PieceColor::WHITE ? 3 : 4;
    if (from.rank != startRank)
        return false;
    Tile middleTile = board.getTile(Point{ from.file, middleRank });
    Tile toTile = board.getTile(Point{ from.file, toRank });
    return !middleTile.isOccupied() && !toTile.isOccupied();
}

std::vector<Point> BoardMove::getOtherMoves(Point from) {
    Piece piece = board.getTile(from).getPiece();
    std::vector<Point> moves;
    for (Point point : piece.getNormalMoves()) {
        Point moveTo = from + point;
        if (moveTo.isInsideBoard())
            moves.push_back(moveTo);
    }
    return moves;
}

bool BoardMove::canMove() {
    for (int file = 0; file < 8; file++)
        for (int rank = 0; rank < 8; rank++)
            if (getMoves(Point{ file, rank }).size() > 0)
                return true;
    return false;
}


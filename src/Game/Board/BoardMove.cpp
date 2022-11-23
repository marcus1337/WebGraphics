#include "BoardMove.h"
#include <iostream>
#include "Move.h"

BoardMove::BoardMove(Board _board, PieceColor _moveColor) : board(_board), moveColor(_moveColor), boardCheck(_board, _moveColor) {

}

std::vector<Point> BoardMove::getUnverifiedMoves(Point from) {
    if (!board.getTile(from).isOccupied())
        return {};
    Piece piece = board.getTile(from).getPiece();
    if (piece.color != moveColor)
        return {};
    if (piece.type == PieceType::PAWN)
        return getPawnMoves(from);
    else if (piece.type == PieceType::KING)
        return getKingMoves(from);
    else
        return getOtherMoves(from);
}

std::vector<Point> BoardMove::getMoves(Point from) {
    std::vector<Point> verifiedMoves;
    for (Point to : getUnverifiedMoves(from)) {
        if (canMove(from, to))
            verifiedMoves.push_back(to);
    }
    return verifiedMoves;
}

bool BoardMove::isMoveCausingSelfCheck(Point from, Point to) {
    Board boardCopy = board;
    Piece piece = board.getTile(from).getPiece();
    Move move(from, to, boardCopy);
    move.apply(boardCopy);
    BoardCheck boardCopyCheck(boardCopy, moveColor);
    return boardCopyCheck.isKingChecked();
}

bool BoardMove::canPawnTake(Point to) {
    return canPawnNormalTake(to) || canPawnPassantTake(to);
}

bool BoardMove::canPawnPassantTake(Point to) {
    int passantRank = moveColor == PieceColor::WHITE ? 5 : 2;
    EnPassant& passant = moveColor == PieceColor::BLACK ? board.whitePassant : board.blackPassant;
    if (!passant.isPawnTwoStepped())
        return false;
    if (to.file != passant.getTwoSteppedPawnFile())
        return false;
    return to.rank == passantRank;
}

bool BoardMove::canPawnNormalTake(Point to) {
    Tile tile = board.getTile(to);
    return tile.isOccupied() && tile.getPiece().color != moveColor;
}

std::vector<Point> BoardMove::getKingMoves(Point from) {
    std::vector<Point> moves;
    for (Point point : board.getTile(from).getPiece().getNormalMoves()) {
        Point moveTo = from + point;
        if (moveTo.isInsideBoard())
            moves.push_back(moveTo);
    }
    if (boardCheck.canKingSideCastle())
        moves.push_back(from + Point{ 2,0 });
    if (boardCheck.canQueenSideCastle())
        moves.push_back(from + Point{ -2,0 });

    return moves;
}

bool BoardMove::isPawnPromoteMove(Point to) {
    return to.rank == 0 || to.rank == 7;
}
std::vector<Point> BoardMove::getPawnPromoteMoves(Point to) {
    PieceColor color = to.rank == 7 ? PieceColor::WHITE : PieceColor::BLACK;
    int knightRank = color == PieceColor::WHITE ? 8 : -1;
    int bishopRank = color == PieceColor::WHITE ? 9 : -2;
    int rookRank = color == PieceColor::WHITE ? 10 : -3;
    int queenRank = color == PieceColor::WHITE ? 11 : -4;
    return { Point{to.file, knightRank}, Point{to.file, bishopRank},
        Point{to.file, rookRank}, Point{to.file, queenRank} };
}

std::vector<Point> BoardMove::getPawnNormalMoves(Point from) {
    std::vector<Point> moves;
    for (Point point : board.getTile(from).getPiece().getNormalMoves()) {
        Point move = point + from;
        if (!board.getTile(move).isOccupied()) {
            if (isPawnPromoteMove(move))
                for (Point promoteMove : getPawnPromoteMoves(move))
                    moves.push_back(promoteMove);
            else
                moves.push_back(move);
        }
    }
    return moves;
}
std::vector<Point> BoardMove::getPawnAttackMoves(Point from) {
    PieceColor color = board.getTile(from).getPiece().color;
    std::vector<Point> moves;
    for (Point point : Piece::getPawnNormalAttacks(color)) {
        Point moveTo = point + from;
        if (moveTo.isInsideBoard() && canPawnTake(moveTo)) {
            if (isPawnPromoteMove(moveTo))
                for (Point point : getPawnPromoteMoves(moveTo))
                    moves.push_back(point);
            else
                moves.push_back(moveTo);
        }
    }
    return moves;
}

std::vector<Point> BoardMove::getPawnMoves(Point from) {
    std::vector<Point> moves;

    for (Point move : getPawnAttackMoves(from))
        moves.push_back(move);

    if (canPawnTwoStep(from)) {
        Piece piece = board.getTile(from).getPiece();
        int rankDiff = piece.color == PieceColor::WHITE ? 2 : -2;
        moves.push_back(from + Point{ 0, rankDiff });
    }

    for (Point move : getPawnNormalMoves(from))
        moves.push_back(move);

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

bool BoardMove::canMove(Point from, Point to) {
    Piece fromPiece = board.getTile(from).getPiece();
    return !isTargetBlocked(to) && !board.isPathBlocked(from, to, fromPiece) && !isMoveCausingSelfCheck(from, to);
}

bool BoardMove::isTargetBlocked(Point to) {
    if (to.rank > 7 || to.rank < 0)
        to.rank = to.rank > 7 ? 7 : 0;
    Tile toTile = board.getTile(to);
    return toTile.isOccupied() && toTile.getPiece().color == moveColor;
}

bool BoardMove::canMove() {
    for (int file = 0; file < 8; file++)
        for (int rank = 0; rank < 8; rank++)
            if (getMoves(Point{ file, rank }).size() > 0)
                return true;
    return false;
}


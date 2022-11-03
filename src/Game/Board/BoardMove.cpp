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
    PieceColor color = board.getTile(from).getPiece().color;
    std::vector<Point> attackMoves;
    for (Point point : Piece::getPawnNormalAttacks(color)) {
        Point moveTo = point + from;
        if (moveTo.isInsideBoard() && canPawnTake(moveTo, color))
            attackMoves.push_back(moveTo);
    }
    

    std::vector<Point> allMoves;
    return allMoves;
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



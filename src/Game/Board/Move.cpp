#include "Move.h"

Piece Move::getPromotePiece() {
    int value;
    if (to.rank >= 8)
        value = to.rank - 8; //white promote value
    else
        value = std::abs(to.rank + 1); //black promote value
    Piece promotePiece = piece;
    if (value == 0)
        promotePiece.type = PieceType::KNIGHT;
    else if (value == 1)
        promotePiece.type = PieceType::BISHOP;
    else if (value == 2)
        promotePiece.type = PieceType::ROOK;
    else
        promotePiece.type = PieceType::QUEEN;
    return promotePiece;
}

bool Move::isPromote() {
    return to.rank < 0 || to.rank > 7;
}

bool Move::isPassant(bool toTileOccupied) {
    return to.isInsideBoard() && piece.type == PieceType::PAWN && !toTileOccupied &&
        from.file != to.file && (to.rank == 2 || to.rank == 5);
}

bool Move::isCastleKingSide() {
    return piece.type == PieceType::KING && from.file - to.file < -1;
}

bool Move::isCastleQueenSide() {
    return piece.type == PieceType::KING && from.file - to.file > 1;
}

int Move::getPromoteRank() {
    if (to.rank > 7)
        return 7;
    return 0;
}

Point Move::getPromotePoint() {
    return Point{ to.file, getPromoteRank() };
}
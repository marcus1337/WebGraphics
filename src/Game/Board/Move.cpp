#include "Move.h"

Piece Move::getPromotePiece() {
    int value;
    if (to.rank >= 7)
        value = to.rank - 7; //white promote value
    else
        value = std::abs(to.rank); //black promote value
    return Piece{getPromoteType(value), piece.color};
}

PieceType Move::getPromoteType(int value) {
    if (value == 1)
        return PieceType::KNIGHT;
    else if (value == 2)
        return PieceType::BISHOP;
    else if (value == 3)
        return PieceType::ROOK;
    else if (value == 4)
        return PieceType::QUEEN;
    return PieceType::PAWN;
}

bool Move::isPromote() {
    return piece.type == PieceType::PAWN && (to.rank <= 0 || to.rank >= 7);
}

bool Move::isPassant() {
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
    if (to.rank >= 7)
        return 7;
    return 0;
}

Point Move::getPromotePoint() {
    return Point{ to.file, getPromoteRank() };
}


Move::Move(Point _from, Point _to, Board& board) {
    from = _from;
    to = _to;
    toTileOccupied = board.getTile(to).isOccupied();
    piece = board.getTile(from).getPiece();
}

void Move::apply(Board& board) {
    setCastleState(board);
    setPassantState(board);

    if (isCastleKingSide())
        board.castleKingSide(piece.color);
    else if (isCastleQueenSide())
        board.castleQueenSide(piece.color);
    else if (isPromote())
        movePromote(board);
    else if (isPassant())
        movePassant(board);
    else
        moveNormal(board);
}

void Move::setCastleState(Board& board) {
    Castle& castle = piece.color == PieceColor::WHITE ? board.whiteCastle : board.blackCastle;
    int rookStartRank = piece.color == PieceColor::WHITE ? 0 : 7;
    if (piece.type == PieceType::KING)
        castle.setKingMoved();
    if (from.rank == rookStartRank && from.file == 0)
        castle.setQueenSideRookMoved();
    if (from.rank == rookStartRank && from.file == 7)
        castle.setKingSideRookMoved();
}

void Move::setPassantState(Board& board) {
    EnPassant& passant = piece.color == PieceColor::WHITE ? board.whitePassant : board.blackPassant;
    passant.setTwoSteppedPawnFile(from.file);
    passant.setPawnTwoStepped(piece.type == PieceType::PAWN && !isPromote() && std::abs(from.rank - to.rank) == 2);
}

Point Move::getPassantTakePoint() {
    int takeRank = piece.color == PieceColor::WHITE ? 4 : 3;
    return Point(to.file, takeRank);
}

void Move::movePassant(Board& board) {
    board.clearTile(getPassantTakePoint());
    board.setPiece(to, piece);
    board.clearTile(from);
}

void Move::movePromote(Board& board) {
    board.setPiece(getPromotePoint(), getPromotePiece());
    board.clearTile(from);
}

void Move::moveNormal(Board& board) {
    board.setPiece(to, piece);
    board.clearTile(from);
}

bool Move::isPromoteTypeSet() {
    return isPromote() && getPromotePiece().type != PieceType::PAWN;
}

void Move::setPromoteType(PieceType pieceType) {
    int value = (int) pieceType;
    if (piece.color == PieceColor::BLACK)
        value *= -1;
    to.rank += value;
}

Point Move::getFrom() {
    return from;
}

Point Move::getTo() {
    return to;
}

Piece Move::getPiece() {
    return piece;
}

bool Move::isReady() {
    return !isPromote() || isPromoteTypeSet();
}


#include "Board.h"
#include <iostream>
#include <iomanip>

Board::Board() {
    reset();
}

void Board::setStartPieces(PieceColor pieceColor) {
    setStartLightPieces(pieceColor);
    setStartHeavyPieces(pieceColor);
}

void Board::setStartLightPieces(PieceColor pieceColor) {
    int rank = pieceColor == PieceColor::WHITE ? 1 : 6;
    for (int file = 0; file < 8; file++)
        setPiece(file, rank, Piece{ PieceType::PAWN, pieceColor });
}
void Board::setStartHeavyPieces(PieceColor pieceColor) {
    int rank = pieceColor == PieceColor::WHITE ? 0 : 7;
    setPiece(0, rank, Piece{ PieceType::ROOK, pieceColor });
    setPiece(7, rank, Piece{ PieceType::ROOK, pieceColor });
    setPiece(1, rank, Piece{ PieceType::KNIGHT, pieceColor });
    setPiece(6, rank, Piece{ PieceType::KNIGHT, pieceColor });
    setPiece(2, rank, Piece{ PieceType::BISHOP, pieceColor });
    setPiece(5, rank, Piece{ PieceType::BISHOP, pieceColor });
    setPiece(3, rank, Piece{ PieceType::QUEEN, pieceColor });
    setPiece(4, rank, Piece{ PieceType::KING, pieceColor });
}

void Board::reset() {
    std::cout << "Board: reset()\n";
    clear();
    setStartPieces(PieceColor::WHITE);
    setStartPieces(PieceColor::BLACK);
}

void Board::clear() {
    whiteCastle = Castle();
    blackCastle = Castle();
    whitePassant = EnPassant();
    blackPassant = EnPassant();
    for (int rank = 0; rank < 8; rank++)
        for (int file = 0; file < 8; file++)
            clearTile(file, rank);
}

void Board::print() {
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << ": ";
        for (int file = 0; file < 8; file++)
            std::cout << "[ " << std::setw(9) << std::left << getTile(file, rank).toString() << "] ";
        std::cout << "\n";
    }
}

void Board::clearTile(int file, int rank) {
    board[file][rank] = Tile();
}

void Board::setPiece(int file, int rank, Piece piece) {
    board[file][rank].setPiece(piece);
    board[file][rank].setOccupied(true);
}

Tile Board::getTile(int file, int rank) {
    return board[file][rank];
}

Tile Board::getTile(Point point) {
    return getTile(point.file, point.rank);
}

void Board::setCastleState(Move move) {
    Piece piece = move.piece;
    Castle& castle = piece.color == PieceColor::WHITE ? whiteCastle : blackCastle;
    int rookStartRank = piece.color == PieceColor::WHITE ? 0 : 7;
    if (piece.type == PieceType::KING)
        castle.setKingMoved();
    if (move.from.rank == rookStartRank && move.from.file == 0)
        castle.setQueenSideRookMoved();
    if (move.from.rank == rookStartRank && move.from.file == 7)
        castle.setKingSideRookMoved();
}

void Board::setPassantState(Move move) {
    Piece piece = move.piece;
    EnPassant& passant = piece.color == PieceColor::WHITE ? whitePassant : blackPassant;
    passant.setTwoSteppedPawnFile(move.from.file);
    passant.setPawnTwoStepped(false);
    if (piece.type != PieceType::PAWN || move.isPromote())
        return;
    if (std::abs(move.from.rank - move.to.rank == 2))
        passant.setPawnTwoStepped(true);
}

void Board::movePassant(Move move) {
    int takeRank = move.piece.color == PieceColor::WHITE ? 4 : 3;
    clearTile(move.to.file, takeRank);
    setPiece(move.to.file, move.to.rank, move.piece);
    clearTile(move.from.file, move.from.rank);
}

void Board::movePromote(Move move) {
    setPiece(move.to.file, move.getPromoteRank(), move.getPromotePiece());
    clearTile(move.from.file, move.from.rank);
}

void Board::moveNormal(Move move) {
    setPiece(move.to.file, move.to.rank, move.piece);
    clearTile(move.from.file, move.from.rank);
}

void Board::move(Move move) {
    setCastleState(move);
    setPassantState(move);

    if (move.isCastleKingSide())
        castleKingSide(move.piece.color);
    else if (move.isCastleQueenSide())
        castleQueenSide(move.piece.color);
    else if (move.isPromote())
        movePromote(move);
    else if (move.isPassant(getTile(move.to).isOccupied()))
        movePassant(move);
    else
        moveNormal(move);
}

void Board::castleKingSide(PieceColor color) {
    int rank = color == PieceColor::WHITE ? 0 : 7;
    clearTile(4, rank);
    clearTile(7, rank);
    setPiece(6, rank, Piece{PieceType::KING, color});
    setPiece(5, rank, Piece{PieceType::ROOK, color});
}

void Board::castleQueenSide(PieceColor color) {
    int rank = color == PieceColor::WHITE ? 0 : 7;
    clearTile(0, rank);
    clearTile(4, rank);
    setPiece(2, rank, Piece{ PieceType::KING, color });
    setPiece(3, rank, Piece{ PieceType::ROOK, color });
}

bool Board::isPathBlocked(Point from, Point to, Piece piece) {
    if (!isBlockablePiece(piece))
        return false;

    Point point = from;
    while (point != to) {
        point.closeDistance(to);
        if (point != to && getTile(point).isOccupied())
            return true;
    }
    return false;
}

bool Board::isBlockablePiece(Piece piece) {
    return piece.type == PieceType::BISHOP || piece.type == PieceType::QUEEN || piece.type == PieceType::ROOK;
}

bool Board::isTileOccupiedByColor(Point point, PieceColor color) {
    Tile tile = getTile(point);
    return tile.isOccupied() && tile.getPiece().color == color;
}


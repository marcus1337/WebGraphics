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
        setPiece(file, rank, PieceType::PAWN, pieceColor);
}
void Board::setStartHeavyPieces(PieceColor pieceColor) {
    int rank = pieceColor == PieceColor::WHITE ? 0 : 7;
    setPiece(0, rank, PieceType::ROOK, pieceColor);
    setPiece(7, rank, PieceType::ROOK, pieceColor);
    setPiece(1, rank, PieceType::KNIGHT, pieceColor);
    setPiece(6, rank, PieceType::KNIGHT, pieceColor);
    setPiece(2, rank, PieceType::BISHOP, pieceColor);
    setPiece(5, rank, PieceType::BISHOP, pieceColor);
    setPiece(3, rank, PieceType::QUEEN, pieceColor);
    setPiece(4, rank, PieceType::KING, pieceColor);
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
        std::cout << (rank+1) << ": ";
        for (int file = 0; file < 8; file++)
            std::cout << "[ " << std::setw(9) << std::left << getTile(file, rank).toString() << "] ";
        std::cout << "\n";
    }
}

void Board::clearTile(int file, int rank) {
    board[file][rank] = Tile();
}

void Board::setPiece(int file, int rank, PieceType pieceType, PieceColor pieceColor) {
    board[file][rank].setPiece(Piece{ pieceType, pieceColor });
    board[file][rank].setOccupied(true);
}

Tile Board::getTile(int file, int rank) {
    return board[file][rank];
}

Tile Board::getTile(Point point) {
    return getTile(point.file, point.rank);
}


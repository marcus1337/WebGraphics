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
    char rank = pieceColor == PieceColor::WHITE ? 1 : 6;
    for (int file = 0; file < 8; file++)
        setPiece(file, rank, PieceType::PAWN, pieceColor);
}
void Board::setStartHeavyPieces(PieceColor pieceColor) {
    char rank = pieceColor == PieceColor::WHITE ? 0 : 7;
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
    for (char rank = 0; rank < 8; rank++)
        for (char file = 0; file < 8; file++)
            clearTile(file, rank);
}

void Board::print() {
    for (char rank = 7; rank >= 0; rank--) {
        std::cout << (rank+1) << ": ";
        for (char file = 0; file < 8; file++)
            std::cout << "[ " << std::setw(9) << std::left << board[file][rank].toString() << "] ";
        std::cout << "\n";
    }
}

void Board::clearTile(char file, char rank) {
    board[file][rank] = Tile();
}

void Board::setPiece(char file, char rank, PieceType pieceType, PieceColor pieceColor) {
    board[file][rank].piece = Piece{ pieceType, pieceColor };
    board[file][rank].occupied = true;
}

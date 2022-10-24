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
    board[file][rank].piece = Piece{ pieceType, pieceColor };
    board[file][rank].occupied = true;
}

Tile Board::getTile(int file, int rank) {
    return board[file][rank];
}

bool Board::isKingMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        return whiteKingMoved;
    else
        return blackKingMoved;
}
bool Board::isQueenSideRookMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        return whiteQueenSideRookMoved;
    else
        return blackQueenSideRookMoved;
}
bool Board::isKingSideRookMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        return whiteKingSideRookMoved;
    else
        return blackKingSideRookMoved;
}
void Board::setKingMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        whiteKingMoved = true;
    else
        blackKingMoved = true;
}
void Board::setKingSideRookMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        whiteKingSideRookMoved = true;
    else
        blackKingSideRookMoved = true;
}
void Board::setQueenSideRookMoved(PieceColor color) {
    if (color == PieceColor::WHITE)
        whiteQueenSideRookMoved = true;
    else
        blackQueenSideRookMoved = true;
}

bool Board::isLastMovePawnTwoStep(PieceColor lastMoveColor) {
    if (lastMoveColor == PieceColor::WHITE)
        return whitePawnTwoStepped;
    else
        return blackPawnTwoStepped;
}
void Board::setLastMovePawnTwoStep(PieceColor lastMoveColor, bool value) {
    whitePawnTwoStepped = false;
    blackPawnTwoStepped = false;
    if (value && lastMoveColor == PieceColor::WHITE)
        whitePawnTwoStepped = true;
    else if (value && lastMoveColor == PieceColor::BLACK)
        blackPawnTwoStepped = true;
}
void Board::setTwoSteppedFile(int file) {
    pawnTwoSteppedFile = file;
}

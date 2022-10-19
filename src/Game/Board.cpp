#include "Board.h"
#include <iostream>

Board::Board() {
    reset();
}

void Board::reset() {
    std::cout << "Board: reset()\n";
    clear();
}

void Board::clear() {
    for (char rank = 0; rank < 8; rank++)
        for (char file = 0; file < 8; file++)
            clearTile(file, rank);
}

void Board::print() {
    std::cout << "----Board Values----\n";
    for (char rank = 0; rank < 8; rank++) {
        std::cout << (rank+1) << ": ";
        for (char file = 0; file < 8; file++) {
            std::cout << "[" << getTilePieceName(file, rank) << "] ";
        }
        std::cout << "\n";
    }
}

std::string Board::getTilePieceName(char file, char rank) {
    if (!isOccupied(file, rank))
        return "None";
    std::string name;
    if (getPieceColor(file, rank) == PieceColor::WHITE)
        name += "W_";
    else
        name += "B_";
    if (getPiece(file, rank) == Piece::PAWN)
        name += "Pawn";
    if (getPiece(file, rank) == Piece::KNIGHT)
        name += "Knight";
    if (getPiece(file, rank) == Piece::BISHOP)
        name += "Bishop";
    if (getPiece(file, rank) == Piece::ROOK)
        name += "Rook";
    if (getPiece(file, rank) == Piece::QUEEN)
        name += "Queen";
    if (getPiece(file, rank) == Piece::KING)
        name += "King";
    return name;
}

Piece Board::getPiece(char file, char rank) {
    PieceColor color = getPieceColor(file, rank);
    char value = board[file][rank];
    if (color == PieceColor::BLACK)
        value--;
    return (Piece)(value / 2);
}

PieceColor Board::getPieceColor(char file, char rank) {
    if (board[file][rank] % 2 != 0)
        return PieceColor::BLACK;
    return PieceColor::WHITE;
}

void Board::clearTile(char file, char rank) {
    board[file][rank] = 0;
}

bool Board::isOccupied(char file, char rank) {
    return board[file][rank] != 0;
}

void Board::setPiece(char file, char rank, Piece piece, PieceColor pieceColor) {
    board[file][rank] = getPieceBoardValue(piece, pieceColor);
}

char Board::getPieceBoardValue(Piece piece, PieceColor pieceColor) {
    char value = ((char)piece)*2;
    if (pieceColor == PieceColor::BLACK)
        value++;
    return value;
}
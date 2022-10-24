#include "Board.h"
#include <iostream>
#include <iomanip>

Board::Board() {
    reset();
}

void Board::setStartPieces(PieceColor pieceColor) {
    char pawnsRank = pieceColor == PieceColor::WHITE ? 1 : 6;
    char heavyPiecesRank = pieceColor == PieceColor::WHITE ? 0 : 7;
    for (int file = 0; file < 8; file++)
        setPiece(file, pawnsRank, Piece::PAWN, pieceColor);
    setPiece(0, heavyPiecesRank, Piece::ROOK, pieceColor);
    setPiece(7, heavyPiecesRank, Piece::ROOK, pieceColor);
    setPiece(1, heavyPiecesRank, Piece::KNIGHT, pieceColor);
    setPiece(6, heavyPiecesRank, Piece::KNIGHT, pieceColor);
    setPiece(2, heavyPiecesRank, Piece::BISHOP, pieceColor);
    setPiece(5, heavyPiecesRank, Piece::BISHOP, pieceColor);
    setPiece(3, heavyPiecesRank, Piece::QUEEN, pieceColor);
    setPiece(4, heavyPiecesRank, Piece::KING, pieceColor);
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
        for (char file = 0; file < 8; file++) {
            std::cout << "[ " << std::setw(9) << std::left << getTilePieceName(file, rank) << "] ";
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
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
        setPiece(file, pawnsRank, PieceType::PAWN, pieceColor);
    setPiece(0, heavyPiecesRank, PieceType::ROOK, pieceColor);
    setPiece(7, heavyPiecesRank, PieceType::ROOK, pieceColor);
    setPiece(1, heavyPiecesRank, PieceType::KNIGHT, pieceColor);
    setPiece(6, heavyPiecesRank, PieceType::KNIGHT, pieceColor);
    setPiece(2, heavyPiecesRank, PieceType::BISHOP, pieceColor);
    setPiece(5, heavyPiecesRank, PieceType::BISHOP, pieceColor);
    setPiece(3, heavyPiecesRank, PieceType::QUEEN, pieceColor);
    setPiece(4, heavyPiecesRank, PieceType::KING, pieceColor);
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
            std::string pieceStr = "None";
            if (board[file][rank].occupied)
                pieceStr = board[file][rank].piece.toString();
            std::cout << "[ " << std::setw(9) << std::left << pieceStr << "] ";
        }
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

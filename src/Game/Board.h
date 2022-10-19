
#include <array>
#include <string>

#ifndef BOARD_H
#define BOARD_H

enum class Piece {
    PAWN = 1, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum class PieceColor {
    WHITE = 0, BLACK
};

class Board {
    std::array<std::array<char, 8>, 8> board; //board[FILE][RANK]

public:
    Board();
    void clear();
    void reset();
    void print();
    void clearTile(char file, char rank);
    bool isOccupied(char file, char rank);
    void setPiece(char file, char rank, Piece piece, PieceColor pieceColor);
    char getPieceBoardValue(Piece piece, PieceColor pieceColor);
    std::string getTilePieceName(char file, char rank);
    Piece getPiece(char file, char rank);
    PieceColor getPieceColor(char file, char rank);
    
};

#endif
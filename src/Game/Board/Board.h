
#include <array>
#include <string>
#include "Piece.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<char, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);

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
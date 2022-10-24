
#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);
    void setStartLightPieces(PieceColor pieceColor);
    void setStartHeavyPieces(PieceColor pieceColor);
    void clearTile(int file, int rank);

public:
    Board();
    void clear();
    void reset();
    void print();

    void setPiece(int file, int rank, PieceType pieceType, PieceColor pieceColor);
    Tile getTile(int file, int rank);
    void clearPassant();
    void makeMove(Move move);
    
};

#endif

#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);

public:
    Board();
    void clear();
    void reset();
    void print();
    void clearTile(char file, char rank);

    void setPiece(char file, char rank, PieceType pieceType, PieceColor pieceColor);
    Tile getTile(char file, char rank);
    
};

#endif
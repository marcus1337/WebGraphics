
#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"
#include "Point.h"
#include "Castle.h"
#include "EnPassant.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);
    void setStartLightPieces(PieceColor pieceColor);
    void setStartHeavyPieces(PieceColor pieceColor);
    void clearTile(int file, int rank);
    void clear();

public:
    Board();
    void reset();
    void print();

    void setPiece(int file, int rank, PieceType pieceType, PieceColor pieceColor);
    Tile getTile(int file, int rank);

    Castle whiteCastle, blackCastle;
    EnPassant whitePassant, blackPassant;

    //std::array<std::array<bool, 8>, 8> getThreatenedTiles(PieceColor attackColor);
    //-----put in other class?
    //bool isChecked(PieceColor color);
    //bool canPromotePawn(PieceColor color, int file);
    //bool canCastle(PieceColor color);
    //bool canCastleKingSide(PieceColor color);
    //bool canCastleQueenSide(PieceColor color);
    
};

#endif
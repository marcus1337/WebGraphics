
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
    void clear();
    bool isBlockablePiece(Piece piece);

public:
    Board();
    void reset();
    void print();

    void clearTile(int file, int rank);
    void clearTile(Point point);
    void setPiece(int file, int rank, Piece piece);
    void setPiece(Point point, Piece piece);

    void castleKingSide(PieceColor color);
    void castleQueenSide(PieceColor color);

    Tile getTile(int file, int rank);
    Tile getTile(Point point);
    bool isTileOccupiedByColor(Point point, PieceColor color);

    Castle whiteCastle, blackCastle;
    EnPassant whitePassant, blackPassant;

    bool isPathBlocked(Point from, Point to, Piece piece);
    
};

#endif
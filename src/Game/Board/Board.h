
#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"
#include "Point.h"
#include "Castle.h"
#include "EnPassant.h"
#include "Move.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);
    void setStartLightPieces(PieceColor pieceColor);
    void setStartHeavyPieces(PieceColor pieceColor);
    void clearTile(int file, int rank);
    void clear();

    void setCastleState(Move move);
    void setPassantState(Move move);
    bool isBlockablePiece(Piece piece);

    void movePassant(Move move);
    void movePromote(Move move);
    void moveNormal(Move move);

public:
    Board();
    void reset();
    void print();

    void setPiece(int file, int rank, Piece piece);

    void move(Move move);
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
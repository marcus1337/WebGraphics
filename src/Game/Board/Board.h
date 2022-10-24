
#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"
#include "Point.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);
    void setStartLightPieces(PieceColor pieceColor);
    void setStartHeavyPieces(PieceColor pieceColor);
    void clearTile(int file, int rank);

    bool blackKingMoved = false;
    bool blackQueenSideRookMoved = false;
    bool blackKingSideRookMoved = false;
    bool whiteKingMoved = false;
    bool whiteQueenSideRookMoved = false;
    bool whiteKingSideRookMoved = false;

    bool whitePawnTwoStepped = false;
    bool blackPawnTwoStepped = false;
    int pawnTwoSteppedFile = -1;

public:
    Board();
    void clear();
    void reset();
    void print();

    void setPiece(int file, int rank, PieceType pieceType, PieceColor pieceColor);
    Tile getTile(int file, int rank);

    bool isKingMoved(PieceColor color);
    bool isQueenSideRookMoved(PieceColor color);
    bool isKingSideRookMoved(PieceColor color);
    void setKingMoved(PieceColor color);
    void setKingSideRookMoved(PieceColor color);
    void setQueenSideRookMoved(PieceColor color);

    bool isLastMovePawnTwoStep(PieceColor lastMoveColor);
    void setLastMovePawnTwoStep(PieceColor lastMoveColor, bool value);
    void setTwoSteppedPawnFile(int file);
    int getTwoSteppedPawnFile();
    
};

#endif
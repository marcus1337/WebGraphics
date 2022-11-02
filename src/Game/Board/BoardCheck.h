#include "Board.h"
#include <array>

#ifndef BOARDCHECK_H
#define BOARDCHECK_H

class BoardCheck {

    Board board;
    PieceColor checkColor;
    std::array<std::array<bool, 8>, 8> checks;
    void clearChecks();
    bool isPlaceableTile(Point toPoint);
    bool isBlockablePiece(Piece piece);
    bool isPathBlocked(Point from, Point to, Piece piece);
    void setChecks(Point fromPoint, Piece piece);
    void setChecks();
public:

    BoardCheck(Board _board, PieceColor _checkColor);
    bool isChecked(Point point);

};

#endif
#include "Board.h"
#include <array>

#ifndef BOARDCHECK_H
#define BOARDCHECK_H

class BoardCheck {

    Board board;
    PieceColor checkColor;
    std::array<std::array<bool, 8>, 8> checks;
    void clearChecks();
    void setChecks(Point fromPoint, Piece piece);
    void setChecks();
public:

    BoardCheck(Board _board, PieceColor _checkColor);
    bool isPointChecked(Point point);
    bool isKingChecked();
    bool canKingSideCastle();
    bool canQueenSideCastle();
};

#endif
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
    void setChecks(Point fromPoint, Piece piece);
public:

    BoardCheck(Board _board, PieceColor _checkColor);
    void setChecks();
    bool isChecked(Point point);

};

#endif
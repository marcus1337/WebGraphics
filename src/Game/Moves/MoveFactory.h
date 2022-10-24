#include "Move.h"
#include "MultiMove.h"
#include "Game/Board/Board.h"
#include <vector>

#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

class MoveFactory {

    PieceColor color;
    Board board;

    std::vector<MultiMove> getPawnPromoteMoves(int file, int rank);

    bool isMovable(int file, int rank);
    bool isBlockingCheck(int file, int rank);

    bool canCastleKingSide();
    bool canCastleQueenSide();
    
public:

    MoveFactory(Board board, PieceColor color);

    std::vector<Move> getMoves(int file, int rank);
    std::vector<MultiMove> getMultiMoves(int file, int rank);
    

};

#endif // !ACTION_H

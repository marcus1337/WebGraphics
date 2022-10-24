#include "MoveFactory.h"

MoveFactory::MoveFactory(Board _board, PieceColor _color) : board(_board), color(_color) {

}

std::vector<Move> MoveFactory::getMoves(int file, int rank) {
    if (!isMovable(file, rank))
        return {};
    std::vector<Move> moves;


    return moves;
}
std::vector<MultiMove> MoveFactory::getMultiMoves(int file, int rank) {
    if (!isMovable(file, rank))
        return {};
    std::vector<MultiMove> multiMoves;

    return multiMoves;
}

bool MoveFactory::isMovable(int file, int rank) {
    return board.getTile(file, rank).piece.color == color && board.getTile(file, rank).occupied;
}

bool MoveFactory::canCastleKingSide() {
    
    return true;
}
bool MoveFactory::canCastleQueenSide() {
    
    return true;
}
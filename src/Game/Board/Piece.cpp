#include "Piece.h"

std::string Piece::toString() {
    std::string str = "";
    color == PieceColor::WHITE ? str += "W_" : str += "B_";
    switch (type) {
    case PieceType::PAWN:
        str += "Pawn";
        break;
    case PieceType::KNIGHT:
        str += "Knight";
        break;
    case PieceType::BISHOP:
        str += "Bishop";
        break;
    case PieceType::ROOK:
        str += "Rook";
        break;
    case PieceType::QUEEN:
        str += "Queen";
        break;
    case PieceType::KING:
        str += "King";
        break;
    default:
        break;
    }
    return str;
}
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

std::vector<Point> Piece::getPawnNormalAttacks(PieceColor _color) {
    std::vector<Point> points;
    if (_color == PieceColor::WHITE) {
        points.push_back(Point{ 1,1 });
        points.push_back(Point{ -1,1 });
    }
    else {
        points.push_back(Point{ 1,-1 });
        points.push_back(Point{ -1,-1 });
    }
    return points;
}

std::vector<Point> Piece::getNormalMoves() {
    std::vector<Point> movePoints;
    switch (type) {
    case PieceType::PAWN:
        if (color == PieceColor::WHITE)
            movePoints.push_back(Point{ 0,1 });
        else
            movePoints.push_back(Point{ 0,-1 });
        break;
    case PieceType::KNIGHT:
        movePoints.push_back(Point{ 1,  -2 });
        movePoints.push_back(Point{ -1, -2 });
        movePoints.push_back(Point{ 1,  2 });
        movePoints.push_back(Point{ -1, 2 });
        movePoints.push_back(Point{ -2, 1 });
        movePoints.push_back(Point{ -2, -1 });
        movePoints.push_back(Point{ 2,  1 });
        movePoints.push_back(Point{ 2,  -1 });
        break;
    case PieceType::BISHOP:
        for (int i = 0; i < 7; i++) {
            movePoints.push_back(Point{ i,i });
            movePoints.push_back(Point{ -i,-i });
            movePoints.push_back(Point{ -i,i });
            movePoints.push_back(Point{ i,-i });
        }
        break;
    case PieceType::ROOK:
        for (int i = 0; i < 7; i++) {
            movePoints.push_back(Point{ 0,i });
            movePoints.push_back(Point{ 0,-i });
            movePoints.push_back(Point{ i,0 });
            movePoints.push_back(Point{ -i,0 });
        }
        break;
    case PieceType::QUEEN:
        for (int i = 0; i < 7; i++) {
            movePoints.push_back(Point{ i,i });
            movePoints.push_back(Point{ -i,-i });
            movePoints.push_back(Point{ -i,i });
            movePoints.push_back(Point{ i,-i });

            movePoints.push_back(Point{ 0,i });
            movePoints.push_back(Point{ 0,-i });
            movePoints.push_back(Point{ i,0 });
            movePoints.push_back(Point{ -i,0 });
        }
        break;
    case PieceType::KING:
        movePoints.push_back(Point{ -1,-1 });
        movePoints.push_back(Point{ -1,0 });
        movePoints.push_back(Point{ 0,-1 });
        movePoints.push_back(Point{ 1,1 });
        movePoints.push_back(Point{ 1,0 });
        movePoints.push_back(Point{ 0,1 });
        movePoints.push_back(Point{ -1,1 });
        movePoints.push_back(Point{ 1,-1 });
        break;
    default:
        break;
    }

    return movePoints;
}
#include "Board.h"
#include <iostream>
#include <iomanip>

Board::Board() {
    reset();
}

void Board::setStartPieces(PieceColor pieceColor) {
    setStartLightPieces(pieceColor);
    setStartHeavyPieces(pieceColor);
}

void Board::setStartLightPieces(PieceColor pieceColor) {
    int rank = pieceColor == PieceColor::WHITE ? 1 : 6;
    for (int file = 0; file < 8; file++)
        setPiece(file, rank, Piece{ PieceType::PAWN, pieceColor });
}
void Board::setStartHeavyPieces(PieceColor pieceColor) {
    int rank = pieceColor == PieceColor::WHITE ? 0 : 7;
    setPiece(0, rank, Piece{ PieceType::ROOK, pieceColor });
    setPiece(7, rank, Piece{ PieceType::ROOK, pieceColor });
    setPiece(1, rank, Piece{ PieceType::KNIGHT, pieceColor });
    setPiece(6, rank, Piece{ PieceType::KNIGHT, pieceColor });
    setPiece(2, rank, Piece{ PieceType::BISHOP, pieceColor });
    setPiece(5, rank, Piece{ PieceType::BISHOP, pieceColor });
    setPiece(3, rank, Piece{ PieceType::QUEEN, pieceColor });
    setPiece(4, rank, Piece{ PieceType::KING, pieceColor });
}

void Board::reset() {
    std::cout << "Board: reset()\n";
    clear();
    setStartPieces(PieceColor::WHITE);
    setStartPieces(PieceColor::BLACK);
}

void Board::clear() {
    whiteCastle = Castle();
    blackCastle = Castle();
    whitePassant = EnPassant();
    blackPassant = EnPassant();
    for (int rank = 0; rank < 8; rank++)
        for (int file = 0; file < 8; file++)
            clearTile(file, rank);
}

void Board::print() {
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << (rank + 1) << ": ";
        for (int file = 0; file < 8; file++)
            std::cout << "[ " << std::setw(9) << std::left << getTile(file, rank).toString() << "] ";
        std::cout << "\n";
    }
}

void Board::clearTile(int file, int rank) {
    board[file][rank] = Tile();
}

void Board::setPiece(int file, int rank, Piece piece) {
    board[file][rank].setPiece(piece);
    board[file][rank].setOccupied(true);
}

Tile Board::getTile(int file, int rank) {
    return board[file][rank];
}

Tile Board::getTile(Point point) {
    return getTile(point.file, point.rank);
}

bool Board::isQueenSideRook(Point from, PieceColor color) {
    Tile tile = getTile(from);
    int rookStartRank = color == PieceColor::WHITE ? 0 : 7;
    Point queenSideRookStartPosition = Point{ 0, rookStartRank };
    return tile.isOccupied() && from == queenSideRookStartPosition && tile.getPiece().color == color;
}
bool Board::isKingSideRook(Point from, PieceColor color) {
    Tile tile = getTile(from);
    int rookStartRank = color == PieceColor::WHITE ? 0 : 7;
    Point kingSideRookStartPosition = Point{ 7, rookStartRank };
    return tile.isOccupied() && from == kingSideRookStartPosition && tile.getPiece().color == color;
}

void Board::setCastleState(Point fromMove) {
    Piece piece = getTile(fromMove).getPiece();
    Castle& castle = piece.color == PieceColor::WHITE ? whiteCastle : blackCastle;
    if (piece.type == PieceType::KING)
        castle.setKingMoved();
    if (isQueenSideRook(fromMove, piece.color))
        castle.setQueenSideRookMoved();
    if (isKingSideRook(fromMove, piece.color))
        castle.setKingSideRookMoved();
}

void Board::setPassantState(Point from, Point to) {
    Piece piece = getTile(from).getPiece();
    EnPassant& passant = piece.color == PieceColor::WHITE ? whitePassant : blackPassant;
    passant.setTwoSteppedPawnFile(from.file);
    passant.setPawnTwoStepped(false);
    if (piece.type != PieceType::PAWN)
        return;
    if (isPromoteMove(to))
        return;
    int rankSteps = std::abs(from.rank - to.rank);
    if (rankSteps == 2)
        passant.setPawnTwoStepped(true);
}

bool Board::isPromoteMove(Point toMove) {
    return toMove.rank < 0 || toMove.rank > 7;
}

PieceType Board::getPromoteType(int toRank) {
    int value;
    if (toRank > 0)
        value = toRank - 8;
    else
        value = std::abs(toRank);
    if (value == 0)
        return PieceType::KNIGHT;
    else if (value == 1)
        return PieceType::BISHOP;
    else if (value == 2)
        return PieceType::ROOK;
    else
        return PieceType::QUEEN;
}

bool Board::isCastleKingSideMove(Point from, Point to) {
    return getTile(from).getPiece().type == PieceType::KING && from.file - to.file < -1;
}
bool Board::isCastleQueenSideMove(Point from, Point to) {
    return getTile(from).getPiece().type == PieceType::KING && from.file - to.file > 1;
}

bool Board::isPassantMove(Point from, Point to) {
    Piece piece = getTile(from).getPiece();
    return piece.type == PieceType::PAWN && !getTile(to).isOccupied() && from.file != to.file && (to.rank == 2 || to.rank == 5);
}

void Board::movePiece(Point from, Point to) {
    setCastleState(from);
    setPassantState(from, to);

    Piece piece = getTile(from).getPiece();
    PieceColor color = piece.color;

    if (isCastleKingSideMove(from, to))
        castleKingSide(color);
    else if (isCastleQueenSideMove(from, to))
        castleQueenSide(color);
    else if (isPassantMove(from, to)) {
        int takeRank = color == PieceColor::WHITE ? 5 : 2;
        clearTile(to.file, takeRank);
    }else if (isPromoteMove(to)) {
        int promoteRank = color == PieceColor::WHITE ? 7 : 0;
        piece = Piece{ getPromoteType(to.rank), color };
        to = Point{ to.file, promoteRank };
    }
    
    setPiece(to.file, to.rank, piece);
    clearTile(from.file, from.rank);
}

void Board::castleKingSide(PieceColor color) {
    int rank = color == PieceColor::WHITE ? 0 : 7;
    movePiece(Point{ 4, rank }, Point{ 6, rank });
    movePiece(Point{ 7, rank }, Point{ 5, rank });
}

void Board::castleQueenSide(PieceColor color) {
    int rank = color == PieceColor::WHITE ? 0 : 7;
    movePiece(Point{ 0, rank }, Point{ 3, rank });
    movePiece(Point{ 4, rank }, Point{ 2, rank });
}

bool Board::isPlaceableTile(Point toPoint, PieceColor newColor) {
    bool insideBoard = toPoint.file >= 0 && toPoint.file <= 7 && toPoint.rank >= 0 && toPoint.rank <= 7;
    if (!insideBoard)
        return false;
    Tile tile = getTile(toPoint.file, toPoint.rank);
    return !tile.isOccupied() || tile.getPiece().color != newColor;
}

bool Board::isPathBlocked(Point from, Point to, Piece piece) {
    if (!isBlockablePiece(piece))
        return false;
    while (from != to) {
        from.closeDistance(to);
        if (from != to && getTile(from).isOccupied())
            return true;
    }
    return false;
}

bool Board::isBlockablePiece(Piece piece) {
    return piece.type == PieceType::BISHOP || piece.type == PieceType::QUEEN || piece.type == PieceType::ROOK;
}

bool Board::isTileOccupiedByColor(Point point, PieceColor color) {
    Tile tile = getTile(point);
    return tile.isOccupied() && tile.getPiece().color == color;
}
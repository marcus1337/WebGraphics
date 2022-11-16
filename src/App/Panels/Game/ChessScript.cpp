#include "ChessScript.h"

ChessScript::ChessScript(UIScript& uiScript) {
    bindMethods(uiScript);
    uiScript.addMethod("getChessRef", [chess = &chess]() {
        return chess;
        });
    chess.print();
}

void ChessScript::bindMethods(UIScript& uiScript) {
    sol::state& lua = uiScript.getStateRef();
    lua.new_usertype<Point>("Point",
        sol::constructors<Point(), Point(int, int)>(),
        "file", &Point::file,
        "rank", &Point::rank,
        "toString", &Point::toString);

    lua.new_enum<PieceType>("PieceType", {
        {"PAWN", PieceType::PAWN},
        {"KING", PieceType::KING},
        {"BISHOP", PieceType::BISHOP},
        {"ROOK", PieceType::ROOK},
        {"QUEEN", PieceType::QUEEN},
        {"KNIGHT", PieceType::KNIGHT} });

    lua.new_enum<PieceColor>("PieceColor", {
    {"WHITE", PieceColor::WHITE},
    {"BLACK", PieceColor::BLACK} });

    lua.new_usertype<Piece>("Piece",
        "type", &Piece::type,
        "color", &Piece::color);

    lua.new_usertype<Tile>("Tile",
        "isOccupied", &Tile::isOccupied,
        "getPiece", &Tile::getPiece);

    lua.new_usertype<Chess>("Chess",
        "reset", &Chess::reset,
        "print", &Chess::print,
        "getTurnColor", &Chess::getTurnColor,
        "isCheck", &Chess::isCheck,
        "isDraw", &Chess::isDraw,
        "isCheckMate", &Chess::isCheckMate,
        "move", &Chess::move,
        "getMoves", &Chess::getMoves,
        "getTile", &Chess::getTile,
        "getTurn", &Chess::getTurn,

        "isPromoteMove", &Chess::isPromoteMove,
        "getHumanMoves", &Chess::getHumanMoves,
        "promote", &Chess::promote);
}
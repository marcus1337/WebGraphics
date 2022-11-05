#include "GamePanel.h"

void GamePanel::onEnter() {
    std::cout << "onEnter() GamePanel" << std::endl;
}
GamePanel::GamePanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "game", _panelContext) {

    addChessTypesToLua(uiScript.getStateRef());
    uiScript.addMethod("getChessRef", [chess = &chess]() {
        return chess;
        });
    uiScript.load();

    chess.print();
}
void GamePanel::update() {

}

void GamePanel::addChessTypesToLua(sol::state& lua) {
    lua.new_usertype<Point>("Point",
        sol::constructors<Point(), Point(int, int)>(),
        "file", &Point::file,
        "rank", &Point::rank);

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

    lua.new_usertype<Chess>("Chess",
        "reset", &Chess::reset,
        "print", &Chess::print,
        "isWhiteTurn", &Chess::isWhiteTurn,
        "isBlackTurn", &Chess::isBlackTurn,
        "isCheck", &Chess::isCheck,
        "isDraw", &Chess::isDraw,
        "isOccupied", &Chess::isOccupied,
        "isCheckMate", &Chess::isCheckMate,
        "move", &Chess::move,
        "getMoves", &Chess::getMoves,
        "getPiece", &Chess::getPiece,
        "getTurn", &Chess::getTurn);
}

void GamePanel::render() {

}

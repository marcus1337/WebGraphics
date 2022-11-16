#include "App/Panels/Panel.h"
#include "Game/Chess.h"

#ifndef CHESS_SCRIPT_H
#define CHESS_SCRIPT_H

class ChessScript {
    Chess chess;

    void bindMethods(UIScript& uiScript);
public:
    ChessScript(UIScript& uiScript);

};

#endif

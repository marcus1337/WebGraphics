#include <memory>
#include <iostream>
#include "Game/TicTacToe.h"
#include "UI/Widgets/Button.h"

#ifndef BOARDBUTTON_H
#define BOARDBUTTON_H

class BoardButton {

    TicTacToe& ticTacToe;
    int row, col;
    Engine& engine;
    std::unique_ptr<Button> button;
    void setPosition();
    void setDefaultVisuals();
    void setCircleVisuals();
    void setCrossVisuals();
    void makeButton();
    void setMarkedVisuals();

public:

    BoardButton(Engine& engine, int _row, int _col, TicTacToe& _ticTacToe);
    void onReset();
    void onPress();
    void update();
    void render();

};


#endif
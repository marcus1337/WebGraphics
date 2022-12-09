#include "App/Panels/Panel.h"
#include "Game/TicTacToe.h"
#include "UI/Widgets/Button.h"
#include "Drawables/Image.h"
#include <array>
#include <memory>
#include <iostream>
#include "BoardButton.h"
#include "Game/AI.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {

    TicTacToe ticTacToe;
    AI ai;
    uint64_t aiDelayCounter = 0;

    std::array<std::unique_ptr<BoardButton>, 9> boardButtons;
    std::unique_ptr<Button> resetButton;
    std::unique_ptr<Image> backgroundImage;

    virtual void onEnter() override;
    void setBoardButtons();
    void makeResetButton();
    void makeBackgroundImage();
    void renderGameOverText();
    void handleAIMove();
    bool isPlayerTurn();
    void updateGame();
    
public:
    GamePanel(Engine& _engine, PanelContext& _panelContext);
    void update() override;
    void render() override;
};

#endif
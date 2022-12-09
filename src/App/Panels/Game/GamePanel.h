#include "App/Panels/Panel.h"
#include "Game/TicTacToe.h"
#include "UI/Widgets/Button.h"
#include "Drawables/Image.h"
#include <array>
#include <memory>
#include <iostream>
#include "BoardButton.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {

    TicTacToe ticTacToe;
    std::array<std::unique_ptr<BoardButton>, 9> boardButtons;
    std::unique_ptr<Button> resetButton;
    std::unique_ptr<Image> backgroundImage;

    virtual void onEnter() override;
    void setBoardButtons();
    void makeResetButton();
    void makeBackgroundImage();
    void renderGameOverText();
    
public:
    GamePanel(Engine& _engine, PanelContext& _panelContext);
    void update() override;
    void render() override;
};

#endif
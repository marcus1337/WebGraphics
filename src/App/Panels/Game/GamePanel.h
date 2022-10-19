#include "App/Panels/Panel.h"
#include "Game/Chess.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {
    virtual void onEnter() override;
    Chess chess;

public:
    GamePanel(Engine& _engine, PanelContext& _panelContext);
    void update() override;
    void render() override;
};

#endif
#include "App/Panels/Panel.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {
    virtual void onEnter() override;

public:
    GamePanel(Engine& _engine, PanelContext& _panelContext);
    void update() override;
    void render() override;
};

#endif
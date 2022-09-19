#include "App/Panels/Panel.h"
#include "GameView.h"
#include "Game/GameDemo.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {
    virtual void onEnter() override;
    GameView gameView;
    GameDemo game;
public:
    GamePanel(Engine& _engine);
    void update() override;
    void render() override;
};

#endif
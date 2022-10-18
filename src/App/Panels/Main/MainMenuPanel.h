
#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenuPanel : public Panel {
    virtual void onEnter() override;
public:
    MainMenuPanel(Engine& _engine, PanelContext& _panelContext);
    void update() override;
    void render() override;
};

#endif // !MAINMENU_H

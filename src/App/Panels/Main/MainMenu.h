
#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu : public Panel {
    virtual void onEnter() override;
public:
    MainMenu(Engine& _engine);
    void update() override;
    void render() override;
};

#endif // !MAINMENU_H

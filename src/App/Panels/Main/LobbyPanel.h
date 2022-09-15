#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"

#ifndef LOBBYPANEL_H
#define LOBBYPANEL_H

class LobbyPanel : public Panel {
    virtual void onEnter() override;
public:
    LobbyPanel(Engine& _engine);
    void update() override;
    void render() override;
};

#endif
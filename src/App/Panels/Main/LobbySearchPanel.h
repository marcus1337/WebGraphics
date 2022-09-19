#include "App/Panels/Panel.h"

#ifndef LOBBYSEARCHPANEL_H
#define LOBBYSEARCHPANEL_H

class LobbySearchPanel : public Panel {
    virtual void onEnter() override;
public:
    LobbySearchPanel(Engine& _engine);
    void update() override;
    void render() override;
};


#endif // !LOBBYSEARCHPANEL_H

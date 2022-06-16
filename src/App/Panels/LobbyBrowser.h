
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>
#include "../Network/DemoLobbyNet.h"

#ifndef LOBBYBROWSER_H
#define LOBBYBROWSER_H

class LobbyBrowser : public Panel {

    Image backgroundImage;
    Button backButton;
    DemoLobbyNet& lobbyNet;

public:

    LobbyBrowser(Engine& _engine, DemoLobbyNet& _lobbyNet);
    void update() override;
    void render() override;


};

#endif
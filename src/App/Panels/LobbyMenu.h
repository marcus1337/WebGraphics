#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>
#include "../Network/DemoLobbyNet.h"

#ifndef LOBBYMENU_H
#define LOBBYMENU_H

class LobbyMenu : public Panel {

    Image backgroundImage;
    Button backButton;
    DemoLobbyNet& lobbyNet;

public:

    LobbyMenu(Engine& _engine, DemoLobbyNet& _lobbyNet);
    void update() override;
    void render() override;

};


#endif // !LOBBYMENU_H

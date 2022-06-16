
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>
#include "../Network/DemoLobbyNet.h"

#ifndef LOBBYBROWSER_H
#define LOBBYBROWSER_H

struct LobbyButton {
    Button button;
    NetID<int> lobbyID;
};

class LobbyBrowser : public Panel {

    Image backgroundImage;
    Button backButton, refreshButton;
    DemoLobbyNet& lobbyNet;

    std::vector<LobbyButton> lobbyButtons;
    LobbyButton makeLobbyButton(NetID<int> lobbyID);
    void setLobbyButtons();
    void handleLobbyButtonClick();
    void onRefresh();

public:

    LobbyBrowser(Engine& _engine, DemoLobbyNet& _lobbyNet);
    void update() override;
    void render() override;


};

#endif
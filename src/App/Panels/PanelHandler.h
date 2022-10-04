#include "App/Panels/Panel.h"

//<Panels>
//Main
#include "App/Panels/Main/MainMenuPanel.h"
#include "App/Panels/Main/InstructionsPanel.h"
#include "App/Panels/Main/SettingsPanel.h"
//Network
#include "App/Panels/Lobby/LobbyPanel.h"
#include "App/Panels/Lobby/LobbySearchPanel.h"
//Game
#include "App/Panels/Game/GameController.h"
#include "App/Panels/Game/GamePanel.h"
//</Panels>

#include <stack>
#include "Engine/Engine.h"
#include <string>

#ifndef PANELHANDLER_H
#define PANELHANDLER_H

class PanelHandler {
    Engine& engine;
    std::stack<Panel*> panels;
    void changePanel();

public:

    PanelHandler(Engine& _engine);
    ~PanelHandler();
    void update();
    void render();

};

#endif
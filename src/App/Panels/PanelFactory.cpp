#include "PanelFactory.h"
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

PanelFactory::PanelFactory(Engine& _engine) : engine(_engine) {

}

Panel* PanelFactory::getNewPanel(PanelType panelType) {
    Panel* newPanel = nullptr;
    using enum PanelType;
    switch (panelType) {
    case SETTINGS:
        newPanel = new SettingsPanel(engine);
        break;
    case INSTRUCTIONS:
        newPanel = new InstructionsPanel(engine);
        break;
    case LOBBY_HOST:
        newPanel = new LobbyPanel(engine);
        break;
    case LOBBY_SEARCH:
        newPanel = new LobbySearchPanel(engine);
        break;
    case GAME:
        newPanel = new GamePanel(engine);
        break;
    default:
        break;
    }
    return newPanel;
}
#include "PanelFactory.h"
//<Panels>
#include "App/Panels/Main/MainMenuPanel.h"
#include "App/Panels/Main/InstructionsPanel.h"
#include "App/Panels/Main/SettingsPanel.h"
#include "App/Panels/Game/GamePanel.h"
//</Panels>

PanelFactory::PanelFactory(Engine& _engine) : engine(_engine) {

}

Panel* PanelFactory::getNewPanel(PanelType panelType) {
    Panel* newPanel = nullptr;
    using enum PanelType;
    switch (panelType) {
    case MAIN_MENU:
        newPanel = new MainMenuPanel(engine, panelContext);
        break;
    case SETTINGS:
        newPanel = new SettingsPanel(engine, panelContext);
        break;
    case INSTRUCTIONS:
        newPanel = new InstructionsPanel(engine, panelContext);
        break;
    case GAME:
        newPanel = new GamePanel(engine, panelContext);
        break;
    default:
        break;
    }
    return newPanel;
}
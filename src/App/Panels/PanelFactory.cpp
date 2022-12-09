#include "PanelFactory.h"
//<Panels>
#include "App/Panels/Game/GamePanel.h"
//</Panels>

PanelFactory::PanelFactory(Engine& _engine) : engine(_engine) {

}

Panel* PanelFactory::getNewPanel(PanelType panelType) {
    Panel* newPanel = nullptr;
    using enum PanelType;
    switch (panelType) {
    case GAME:
        newPanel = new GamePanel(engine, panelContext);
        break;
    default:
        break;
    }
    return newPanel;
}
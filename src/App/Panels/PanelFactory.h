#include "App/Panels/Panel.h"
#include "App/Panels/PanelContext.h"

#ifndef PANELFACTORY_H
#define PANELFACTORY_H

class PanelFactory {
    Engine& engine;
    PanelContext panelContext;
public:
    PanelFactory(Engine& _engine);
    Panel* getNewPanel(PanelType panelType);
};

#endif // !PANELFACTORY_H

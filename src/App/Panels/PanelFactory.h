#include "App/Panels/Panel.h"

#ifndef PANELFACTORY_H
#define PANELFACTORY_H

class PanelFactory {
    Engine& engine;
public:
    PanelFactory(Engine& _engine);
    Panel* getNewPanel(PanelType panelType);
};

#endif // !PANELFACTORY_H

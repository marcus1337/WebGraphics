#include "App/Panels/Panel.h"
#include "App/Panels/PanelFactory.h"

#include <stack>
#include "Engine/Engine.h"
#include <string>

#ifndef PANELHANDLER_H
#define PANELHANDLER_H

class PanelHandler {
    Engine& engine;
    std::stack<Panel*> panels;
    void changePanel();
    PanelFactory panelFactory;

public:

    PanelHandler(Engine& _engine);
    ~PanelHandler();
    void update();
    void render();

};

#endif
#include <Engine/Engine.h>
#include <stack>
#include <string>
#include <functional>
#include "PanelContext.h"

#ifndef PANEL_H
#define PANEL_H

enum class PanelType {
    NONE = 0, GAME
};

class Panel {
private:
    PanelType childPanel = PanelType::NONE;
    bool done = false;
protected:
    Engine& engine;
    Graphics& graphics;
    PanelContext& panelContext;
public:
    Panel(Engine& _engine, std::string uiScriptName, PanelContext& _panelContext);
    bool isDone();
    virtual ~Panel() = default;
    virtual void update();
    virtual void render();
    virtual void onEnter();
    PanelType getChildPanel();
    void setChildPanel(PanelType panelType);

    void onQuit();
    void onCancel();
};

#endif
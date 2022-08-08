
#include <Engine/Engine.h>
#include <stack>

#ifndef PANEL_H
#define PANEL_H

enum class PanelStatus {
    RUNNING = 0, FINISHED, PAUSED
};

class Panel {
protected:
    Engine& engine;
    Graphics& graphics;
    void onExit();

public:
    PanelStatus panelStatus;
    Panel(Engine& _engine);
    virtual ~Panel() = default;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onEnter();
    Panel* childPanel = nullptr;
};

#endif
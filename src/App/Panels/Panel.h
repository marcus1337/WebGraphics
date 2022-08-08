
#include <Engine/Engine.h>
#include <stack>
#include <Drawables/Button.h>

#ifndef PANEL_H
#define PANEL_H

enum class PanelStatus {
    RUNNING = 0, FINISHED, PAUSED
};

class Panel {
protected:
    Engine& engine;
    Graphics& graphics;
    std::vector<Button*> buttons;
    void updateButtons();
    void renderButtons();
    void renderButton(Button& button);
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
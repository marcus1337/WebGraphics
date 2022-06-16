
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
    std::vector<Button*> buttons;
    void updateButtons(int _x, int _y);
    void renderButtons();
    void updateButton(Button& button, int _x, int _y);
    void renderButton(Button& button);

    int getRelativeMouseXPosition();
    int getRelativeMouseYPosition();
    void onExit();

public:
    PanelStatus panelStatus;
    Panel(Engine& _engine);
    virtual void update() = 0;
    virtual void render() = 0;
    Panel* childPanel = nullptr;
};

#endif
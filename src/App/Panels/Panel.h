#include <Engine/Engine.h>
#include <stack>
#include <string>
#include <UI/UIScript.h>

#ifndef PANEL_H
#define PANEL_H

enum class PanelType {
    NONE = 0, SETTINGS, INSTRUCTIONS, LOBBY_HOST, LOBBY_SEARCH, GAME
};

class Panel {
private:
    PanelType childPanel = PanelType::NONE;
    void onQuit();
    void onCancel();
    bool done = false;
protected:
    UIScript uiScript;
    Engine& engine;
    Graphics& graphics;
public:
    Panel(Engine& _engine, std::string uiScriptName);
    bool isDone();
    virtual ~Panel() = default;
    virtual void update();
    virtual void render();
    void updateUI();
    void renderUI();
    virtual void onEnter();
    PanelType getChildPanel();
    void setChildPanel(PanelType panelType);
};

#endif
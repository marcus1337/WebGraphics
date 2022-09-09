
#include <Engine/Engine.h>
#include <stack>
#include <string>
#include <UI/UIScript.h>

#ifndef PANEL_H
#define PANEL_H

class Panel {
private:
    Panel* childPanel = nullptr;
    void onQuit();
    void onCancel();
protected:
    UIScript uiScript;
    Engine& engine;
    Graphics& graphics;
    bool done = false;
    void setChildPanel(Panel* _panel);
public:
    Panel(Engine& _engine, std::string uiScriptName);
    bool isDone();
    virtual ~Panel() = default;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onEnter();
    Panel* getChildPanel();
};

#endif

#include <Engine/Engine.h>
#include <stack>

#ifndef PANEL_H
#define PANEL_H

class Panel {
private:
    Panel* childPanel = nullptr;
protected:
    Engine& engine;
    Graphics& graphics;
    void setDone();
    bool done = false;
    void setChildPanel(Panel* _panel);
public:
    Panel(Engine& _engine);
    bool isDone();
    virtual ~Panel() = default;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onEnter();
    Panel* getChildPanel();
};

#endif
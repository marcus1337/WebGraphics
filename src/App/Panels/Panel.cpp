#include "App/Panels/Panel.h"
#include <assert.h>

Panel::Panel(Engine &_engine) : engine(_engine), graphics(_engine.graphics)
{
}

void Panel::onEnter()
{
}

void Panel::setDone() {
    done = true;
}

bool Panel::isDone() {
    return done;
}

Panel* Panel::getChildPanel() {
    Panel* _panel = childPanel;
    childPanel = nullptr;
    return _panel;
}

void Panel::setChildPanel(Panel* _panel) {
    assert(childPanel == nullptr);
    childPanel = _panel;
}
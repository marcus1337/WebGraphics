#include "App/Panels/Panel.h"
#include <assert.h>

Panel::Panel(Engine &_engine, std::string uiScriptName) : engine(_engine), graphics(_engine.graphics), uiScript(uiScriptName, _engine)
{
    uiScript.addMethod("onQuit", std::bind(&Panel::onQuit, this));
    uiScript.addMethod("onCancel", std::bind(&Panel::onCancel, this));
}

void Panel::onEnter()
{
}

bool Panel::isDone() {
    return done;
}

Panel* Panel::getChildPanel() {
    Panel* _panel = childPanel;
    childPanel = nullptr;
    return _panel;
}

bool Panel::canSetChildPanel() {
    return childPanel == nullptr;
}

void Panel::setChildPanel(Panel* _panel) {
    assert(childPanel == nullptr);
    childPanel = _panel;
}

void Panel::onCancel() {
    std::cout << "onCancel()\n";
    done = true;
}

void Panel::onQuit() {
    std::cout << "onQuit()\n";
    exit(0);
}

void Panel::updateUI() {
    uiScript.update();
}

void Panel::renderUI() {
    uiScript.render();
}

void Panel::update() {

}
void Panel::render() {

}
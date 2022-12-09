#include "App/Panels/Panel.h"
#include <assert.h>

Panel::Panel(Engine &_engine, std::string uiScriptName, PanelContext& _panelContext) : engine(_engine), graphics(_engine.graphics), panelContext(_panelContext)
{

}

void Panel::onEnter()
{
}

bool Panel::isDone() {
    return done;
}

PanelType Panel::getChildPanel() {
    return childPanel;
}
void Panel::setChildPanel(PanelType panelType) {
    childPanel = panelType;
}

void Panel::onCancel() {
    std::cout << "onCancel()\n";
    done = true;
}

void Panel::onQuit() {
    std::cout << "onQuit()\n";
#ifndef EMSCRIPTEN
    exit(0);
#endif // !EMSCRIPTEN
}

void Panel::update() {

}
void Panel::render() {

}
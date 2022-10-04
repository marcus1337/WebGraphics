#include "App/Panels/Panel.h"
#include <assert.h>

Panel::Panel(Engine &_engine, std::string uiScriptName) : engine(_engine), graphics(_engine.graphics), uiScript(uiScriptName, _engine)
{
    uiScript.addMethod("onQuit", std::bind(&Panel::onQuit, this));
    uiScript.addMethod("onCancel", std::bind(&Panel::onCancel, this));

    uiScript.addMethod("onSettings", [&]() {
        setChildPanel(PanelType::SETTINGS);
        });
    uiScript.addMethod("onLobby", [&]() {
        setChildPanel(PanelType::LOBBY_HOST);
        });
    uiScript.addMethod("onGame", [&]() {
        setChildPanel(PanelType::GAME);
        });
    uiScript.addMethod("onFindLobby", [&]() {
        setChildPanel(PanelType::LOBBY_SEARCH);
        });
    uiScript.addMethod("onInstructions", [&]() {
        setChildPanel(PanelType::INSTRUCTIONS);
        });
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
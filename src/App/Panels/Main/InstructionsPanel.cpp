#include "InstructionsPanel.h"

void InstructionsPanel::onEnter() {
    std::cout << "onEnter() Instructions\n";
}
InstructionsPanel::InstructionsPanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "instructions", _panelContext) {
    uiScript.load();
}
void InstructionsPanel::update() {

}
void InstructionsPanel::render() {

}
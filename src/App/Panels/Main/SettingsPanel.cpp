#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "settings", _panelContext) {
    uiScript.load();
}

void SettingsPanel::onEnter() {
    std::cout << "onEnter() Settings\n";
}



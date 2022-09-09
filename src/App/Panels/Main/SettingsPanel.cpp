#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(Engine& _engine) : Panel(_engine, "settings") {

}

void SettingsPanel::onEnter() {
    std::cout << "onEnter() Settings\n";

}



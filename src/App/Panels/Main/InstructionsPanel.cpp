#include "InstructionsPanel.h"

void InstructionsPanel::onEnter() {
    std::cout << "onEnter() Instructions\n";
}
InstructionsPanel::InstructionsPanel(Engine& _engine) : Panel(_engine, "instructions") {
    
}
void InstructionsPanel::update() {

}
void InstructionsPanel::render() {

}
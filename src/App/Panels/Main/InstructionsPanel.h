#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"

#ifndef INSTRUCTIONSPANEL_H
#define INSTRUCTIONSPANEL_H

class InstructionsPanel : public Panel {
    virtual void onEnter() override;
public:
    InstructionsPanel(Engine& _engine);
    void update() override;
    void render() override;
};

#endif // !INSTRUCTIONSPANEL_H

#include "App/Panels/Panel.h"

Panel::Panel(Engine &_engine) : panelStatus(PanelStatus::RUNNING), engine(_engine), graphics(_engine.graphics)
{
}

void Panel::onExit()
{
    panelStatus = PanelStatus::FINISHED;
}

void Panel::onEnter()
{
}

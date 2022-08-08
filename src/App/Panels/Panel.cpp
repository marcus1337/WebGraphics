#include "App/Panels/Panel.h"

Panel::Panel(Engine &_engine) : panelStatus(PanelStatus::RUNNING), engine(_engine), graphics(_engine.graphics)
{
}

void Panel::updateButtons()
{
    for (int i = 0; i < buttons.size(); i++)
    {
        (*buttons[i]).update(engine.graphics, engine.window.mouse);
    }
}

void Panel::renderButtons()
{
    for (Button *button : buttons)
        renderButton(*button);
}

void Panel::renderButton(Button &button)
{
    button.render(engine.graphics, engine.window.mouse);
}

void Panel::onExit()
{
    panelStatus = PanelStatus::FINISHED;
}

void Panel::onEnter()
{
}

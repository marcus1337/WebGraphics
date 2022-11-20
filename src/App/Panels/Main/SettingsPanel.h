#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"
#include <UI/Widgets/Button.h>
#include <UI/Script/UIScript.h>


#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

class SettingsPanel : public Panel {
    virtual void onEnter() override;
public:
    SettingsPanel(Engine& _engine, PanelContext& _panelContext);
};

#endif // !SETTINGSPANEL_

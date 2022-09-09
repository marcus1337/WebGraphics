#include "Engine/Engine.h"
#include <string>
#include <vector>
#include "App/Panels/Panel.h"
#include <UI/Button.h>
#include <UI/UIScript.h>


#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

class SettingsPanel : public Panel {

    virtual void onEnter() override;
public:
    SettingsPanel(Engine& _engine);
    void update() override;
    void render() override;
};

#endif // !SETTINGSPANEL_

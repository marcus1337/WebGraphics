#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include "../Timer.h"

#ifndef UITYPES_H
#define UITYPES_H

class UITypes {

    sol::state& lua;
    Engine& engine;
    Graphics& graphics;

    void addUIElement();
    void addTimer();
    void addButton();
    void addSlider();

public:

    UITypes(sol::state& _lua, Engine& _engine);
    void setTypes();

};

#endif


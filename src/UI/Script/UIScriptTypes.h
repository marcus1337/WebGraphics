#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include "UITypes.h"
#include "DrawableTypes.h"

#ifndef UISCRIPTTYPES_H
#define UISCRIPTTYPES_H

class UIScriptTypes {
    DrawableTypes drawableTypes;
    UITypes uiTypes;

public:

    UIScriptTypes(sol::state& _lua, Engine& _engine);
    void setTypes();
};

#endif

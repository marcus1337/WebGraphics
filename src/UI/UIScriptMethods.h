#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>

#ifndef UISCRIPTMETHODS_H
#define UISCRIPTMETHODS_H

class UIScriptMethods {
    sol::state& lua;
    Engine& engine;
    Graphics& graphics;
public:
    UIScriptMethods(sol::state& _lua, Engine& _engine);
    void setMethods();
};

#endif // !UISCRIPTMETHODS_H

#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>

#ifndef UISCRIPT_H
#define UISCRIPT_H

class UIScript
{
    sol::state lua;
    sol::load_result script;
    std::string scriptFileName;
    std::string getScriptFilePath();
    void load();

public:
    UIScript(std::string _scriptFileName);
    ~UIScript();
    void render();
    void update();

};

#endif

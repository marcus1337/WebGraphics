#include "UIScript.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

UIScript::UIScript(std::string _scriptFileName) : scriptFileName(_scriptFileName)
{
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package, sol::lib::string, sol::lib::table);
    load();
}

UIScript::~UIScript()
{
}

void UIScript::load()
{
    script = lua.load_file(getScriptFilePath());
    if (!script.valid())
    {
        sol::error err = script;
        std::string what = err.what();
        std::cout << "error: " << what << "\n";
        return;
    }
    script();
    scriptInit = lua["init"];
    scriptUpdate = lua["update"];
    scriptInit();
}

std::string UIScript::getScriptFilePath()
{
    return FolderPaths::getScriptsPath() + scriptFileName + ".lua";
}

void UIScript::render()
{
}

void UIScript::update()
{
    // script();
}

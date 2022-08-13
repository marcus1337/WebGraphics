#include "UIScript.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

UIScript::UIScript(std::string _scriptFileName) : scriptFileName(_scriptFileName), fileChecker(getScriptFilePath())
{
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package, sol::lib::string, sol::lib::table);
    loaded = load();
}

UIScript::~UIScript()
{
}

bool UIScript::load()
{
    script = lua.load_file(getScriptFilePath());
    if (!script.valid())
    {
        sol::error err = script;
        std::string what = err.what();
        std::cout << "Error loading script: " << what << "\n";
        return false;
    }
    sol::protected_function_result result = script();
    if (!result.valid()) {
        sol::error err = result;
        sol::call_status status = result.status();
        std::cout << "Error script-runtime: " << sol::to_string(status) << " error" << "\n\t" << err.what() << std::endl;
        return false;
    }

    lua["init"]();
    scriptUpdate = lua["update"];
    return true;
}

std::string UIScript::getScriptFilePath()
{
    return FolderPaths::getScriptsPath() + scriptFileName + ".lua";
}

void UIScript::render()
{
    if (loaded) {
        // script();
    }
}

void UIScript::update()
{
    if (fileChecker.isChanged()) {
        fileChecker.setUnchanged();
        loaded = load();
        std::cout << "Script was edited.\n";
    }
    if (loaded) {
        // script();
    }
}

#include "UIScript.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <Drawables/View.h>
#include <Drawables/Rect.h>
#include <memory>
#include "Button.h"


UIScript::UIScript(std::string _scriptFileName, Engine& _engine) : scriptFileName(_scriptFileName), fileChecker(getScriptFilePath()), engine(_engine), graphics(_engine.graphics), scriptTypes(lua, _engine)
{
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package, sol::lib::string, sol::lib::table);
    scriptTypes.setUserTypes();
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
        printError(script);
        return false;
    }
    sol::protected_function_result result = testScriptValidity();
    if (!result.valid()) {
        printError(result);
        return false;
    }
    scriptUpdate = lua["update"];
    scriptRender = lua["render"];
    return true;
}

sol::protected_function_result UIScript::testScriptValidity() {
    sol::protected_function_result result = script();
    if (!result.valid())
        return result;
    result = lua["init"]();
    if (!result.valid())
        return result;
    result = lua["update"]();
    if (!result.valid())
        return result;
    result = lua["render"]();
    if (!result.valid())
        return result;
    return result;
}

void UIScript::printError(sol::protected_function_result& result) {
    sol::error err = result;
    sol::call_status status = result.status();
    std::cout << "Error script-runtime: " << sol::to_string(status) << " error" << "\n\t" << err.what() << std::endl;
}

void UIScript::printError(sol::load_result& result) {
    sol::error err = script;
    std::string what = err.what();
    std::cout << "Error loading script: " << what << "\n";
}

std::string UIScript::getScriptFilePath()
{
    return FolderPaths::getScriptsPath() + scriptFileName + ".lua";
}

void UIScript::render()
{
    if (loaded) {
        scriptRender();
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
        scriptUpdate();
    }
}
#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <IO/Files/FileChecker.h>
#include "UIScriptTypes.h"
#include "UIScriptMethods.h"
#include <functional>
#include "UIHelperScripts.h"

#ifndef UISCRIPT_H
#define UISCRIPT_H

class UIScript
{
    Engine& engine;
    Graphics& graphics;

    UIScriptTypes scriptTypes;
    UIScriptMethods scriptMethods;
    UIHelperScripts uiHelperScripts;
    sol::state lua;
    sol::load_result script;
    sol::function scriptUpdate, scriptRender;

    std::string scriptFileName;
    FileChecker fileChecker;
    std::string getScriptFilePath(std::string scriptName);
    bool loaded = false;
    void printError(sol::protected_function_result& result);
    void printError(sol::load_result& result);
    sol::protected_function_result testScriptValidity();

public:
    UIScript(std::string _scriptFileName, Engine& _engine);
    void load();
    ~UIScript();
    void render();
    void update();

    template<typename F>
    void addMethod(std::string methodName, F func) {
        lua[methodName] = func;
    }

    sol::state& getStateRef() {
        return lua;
    }

};

#endif

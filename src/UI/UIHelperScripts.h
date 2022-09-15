#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <IO/Files/FileChecker.h>
#include "UIScriptTypes.h"
#include "UIScriptMethods.h"
#include <functional>

#ifndef UIHELPERSCRIPTS_H
#define UIHELPERSCRIPTS_H

class UIHelperScripts {

    sol::state& lua;
    std::vector<FileChecker> fileCheckers;
    void printError(sol::protected_function_result& result);
    void printError(sol::load_result& result);
    std::string getScriptFilePath(std::string scriptName);

public:
    UIHelperScripts(sol::state& _lua);
    void load();
    bool isAnyScriptChanged();
};

#endif // !UIHELPERSCRIPTS_H

#include "UIHelperScripts.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

UIHelperScripts::UIHelperScripts(sol::state& _lua) : lua(_lua) {
    fileCheckers.push_back(FileChecker(getScriptFilePath("utils")));
    fileCheckers.push_back(FileChecker(getScriptFilePath("utils2")));
}
void UIHelperScripts::load() {
    for (FileChecker& fileChecker : fileCheckers) {
        fileChecker.setUnchanged();
        auto script = lua.load_file(fileChecker.getFilePath());
        if (!script.valid())
        {
            printError(script);
            return;
        }
        sol::protected_function_result result = script();
        if (!result.valid())
        {
            printError(result);
            return;
        }
    }
}

std::string UIHelperScripts::getScriptFilePath(std::string scriptName) {
    return FolderPaths::getScriptsPath() + "ui_utils//" + scriptName + ".lua";
}

bool UIHelperScripts::isAnyScriptChanged() {
    for (FileChecker& fileChecker : fileCheckers) {
        if (fileChecker.isChanged())
            return true;
    }
    return false;
}

void UIHelperScripts::printError(sol::protected_function_result& result) {
    sol::error err = result;
    sol::call_status status = result.status();
    std::cout << "Error script-runtime: " << sol::to_string(status) << " error" << "\n\t" << err.what() << std::endl;
}
void UIHelperScripts::printError(sol::load_result& result) {
    sol::error err = result;
    std::string what = err.what();
    std::cout << "Error loading script: " << what << "\n";
}

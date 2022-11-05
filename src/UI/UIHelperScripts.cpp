#include "UIHelperScripts.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>
#include <filesystem>

UIHelperScripts::UIHelperScripts(sol::state& _lua) : lua(_lua) {
    for (std::string path : getScriptFilePaths()) {
        fileCheckers.push_back(FileChecker(path));
    }
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

std::vector<std::string> UIHelperScripts::getScriptFilePaths() {
    std::vector<std::string> paths;
    for (std::string path : getScriptFilePathsInDirectory(FolderPaths::getScriptsPath() + "ui_utils//"))
        paths.push_back(path);
    for (std::string path : getScriptFilePathsInDirectory(FolderPaths::getScriptsPath() + "ui_game//"))
        paths.push_back(path);
    return paths;
}

std::vector<std::string> UIHelperScripts::getScriptFilePathsInDirectory(std::string directoryPath) {
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        paths.push_back(entry.path().string());
    return paths;
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

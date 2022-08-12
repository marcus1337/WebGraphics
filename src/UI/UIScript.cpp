#include "UIScript.h"
#include <IO/Files/FolderPaths.h>

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
}

std::string UIScript::getScriptFilePath(){
    return FolderPaths::getScriptsPath() + scriptFileName + ".lua";
}

void UIScript::render()
{

}

void UIScript::update()
{
    script();
}



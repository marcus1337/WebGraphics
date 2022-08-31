
#include "UIScriptMethods.h"


UIScriptMethods::UIScriptMethods(sol::state& _lua, Engine& _engine) : lua(_lua), engine(_engine), graphics(_engine.graphics) {

}

void UIScriptMethods::setMethods() {
    lua["isFullScreen"] = [&engine = engine]() {
        return engine.window.isFullScreen();
    };
    lua["setFullScreen"] = [&engine = engine](bool _fullScreen) {
        engine.window.setFullScreen(_fullScreen);
    };
}
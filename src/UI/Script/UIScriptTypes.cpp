
#include "UIScriptTypes.h"


UIScriptTypes::UIScriptTypes(sol::state& _lua, Engine& _engine) : drawableTypes(_lua, _engine), uiTypes(_lua, _engine) {


}

void UIScriptTypes::setTypes() {
    drawableTypes.setTypes();
    uiTypes.setTypes();

}


#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>

#ifndef UISCRIPTTYPES_H
#define UISCRIPTTYPES_H

class UIScriptTypes {

    sol::state& lua;
    Engine& engine;
    Graphics& graphics;

    void addVec();
    void addDrawable();
    void addButton();
    void addSlider();
    void addImage();
    void addText();
    void addView();
    void addRect();
    void addLine();
    void addCircle();
    void addUIElement();
    void addTimer();

public:

    UIScriptTypes(sol::state& _lua, Engine& _engine);
    void setUserTypes();
};

#endif

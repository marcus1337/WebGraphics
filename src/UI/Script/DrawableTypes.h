#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>

#ifndef DRAWABLETYPES_H
#define DRAWABLETYPES_H

class DrawableTypes {

    sol::state& lua;
    Engine& engine;
    Graphics& graphics;

    void addVec();
    void addDrawable();
    void addImage();
    void addText();
    void addView();
    void addRect();
    void addLine();
    void addCircle();

public:

    DrawableTypes(sol::state& _lua, Engine& _engine);
    void setTypes();

};

#endif

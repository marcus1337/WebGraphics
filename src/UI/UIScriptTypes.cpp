
#include "UIScriptTypes.h"

#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <Drawables/View.h>
#include <Drawables/Rect.h>
#include "Button.h"

UIScriptTypes::UIScriptTypes(sol::state& _lua, Engine& _engine) : lua(_lua), engine(_engine), graphics(_engine.graphics) {


}

void UIScriptTypes::setUserTypes() {
    addVec();
    addDrawable();
    addImage();
    addText();
    addRect();
    addView();
    addButton();
}

void UIScriptTypes::addVec() {
    lua.new_usertype<glm::vec3>("vec3",
        sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
        sol::call_constructor, [](float _x, float _y, float _z) {return glm::vec3(_x, _y, _z); });
}

void UIScriptTypes::addDrawable() {
    lua.new_usertype<Drawable>("Drawable",
        "setPosition", &Drawable::setPosition,
        "setSize", &Drawable::setSize,
        "setColor", &Drawable::setColor,
        "setAlpha", &Drawable::setAlpha,
        "setRotation", &Drawable::setRotation,
        "setViewProjectionMatrix", &Drawable::setViewProjectionMatrix,
        "getX", &Drawable::getX,
        "getY", &Drawable::getY,
        "getWidth", &Drawable::getWidth,
        "getHeight", &Drawable::getHeight,
        "setShaderProgram", &Drawable::setShaderProgram,
        "render", &Drawable::render);
}
void UIScriptTypes::addButton() {
    auto btnFactory = sol::factories([&engine = engine]() {
        std::unique_ptr<Button> btn = std::make_unique<Button>(engine);
        return btn; });
    lua.new_usertype<Button>("Button",
        sol::meta_function::construct, btnFactory,
        sol::call_constructor, btnFactory,
        "setPosition", &Button::setPosition,
        "update", &Button::update,
        "render", &Button::render,
        "onPressCallback", &Button::onPressCallback);
}
void UIScriptTypes::addImage() {
    auto imgFactory = sol::factories([&engine = engine]() {
        std::unique_ptr<Image> img = std::make_unique<Image>(engine, "background2.png");
        img->setSize(300, 150);
        img->setPosition(500, 500);
        return img;
        });
    lua.new_usertype<Image>("Image",
        sol::meta_function::construct, imgFactory,
        sol::call_constructor, imgFactory,
        sol::base_classes, sol::bases<Drawable>());
}
void UIScriptTypes::addText() {
    auto textFactory = sol::factories([&engine = engine](std::string _str) {
        std::unique_ptr<Text> text = std::make_unique<Text>(engine);
        text->setText(_str);
        return text;
        });
    lua.new_usertype<Text>("Text",
        sol::meta_function::construct, textFactory,
        sol::call_constructor, textFactory,
        "setText", &Text::setText,
        "getPixelHeight", &Text::getPixelHeight,
        "getPixelWidth", &Text::getPixelWidth,
        "setFont", &Text::setFont,
        "setPixelHeight", &Text::setPixelHeight,
        "center", &Text::center,
        sol::base_classes, sol::bases<Drawable>());
}
void UIScriptTypes::addView() {
    auto viewFactory = sol::factories([&engine = engine](int _width, int _height) {
        std::unique_ptr<View> view = std::make_unique<View>(engine, _width, _height);
        return view;});
    lua.new_usertype<View>("View",
        sol::meta_function::construct, viewFactory,
        sol::call_constructor, viewFactory,
        "clear", &View::clear,
        "paint", &View::paint,
        //getImage()?
        sol::base_classes, sol::bases<Drawable>());
}
void UIScriptTypes::addRect() {
    auto rectFactory = sol::factories([&engine = engine]() {
        std::unique_ptr<Rect> rect = std::make_unique<Rect>(engine);
        rect->setSize(100, 100);
        return rect;
        });
    lua.new_usertype<Rect>("Rect",
        sol::meta_function::construct, rectFactory,
        sol::call_constructor, rectFactory,
        sol::base_classes, sol::bases<Drawable>());
}



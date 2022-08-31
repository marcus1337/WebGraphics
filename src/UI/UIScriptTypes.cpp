
#include "UIScriptTypes.h"

#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <Drawables/View.h>
#include <Drawables/Rect.h>
#include <Drawables/Line.h>
#include <Drawables/Circle.h>
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
    addLine();
    addCircle();
}

void UIScriptTypes::addVec() {
    lua.new_usertype<glm::vec2>("vec2",
        sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
        sol::call_constructor, [](float _x, float _y) {return glm::vec2(_x, _y); });
    lua.new_usertype<glm::vec3>("vec3",
        sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
        sol::call_constructor, [](float _x, float _y, float _z) {return glm::vec3(_x, _y, _z); });
    lua.new_usertype<glm::vec4>("vec4",
        sol::constructors<glm::vec4(), glm::vec4(float), glm::vec4(float, float, float, float)>(),
        sol::call_constructor, [](float _x, float _y, float _z, float _a) {return glm::vec4(_x, _y, _z, _a); });
}

void UIScriptTypes::addDrawable() {
    lua.new_usertype<Drawable>("Drawable",
        "setPosition", &Drawable::setPosition,
        "setEffect", &Drawable::setEffect,
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
        "setText", &Button::setText,
        "setImage", &Button::setImage,
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
        return view; });
    lua.new_usertype<View>("View",
        sol::meta_function::construct, viewFactory,
        sol::call_constructor, viewFactory,
        "clear", &View::clear,
        "paint", &View::paint,
        "setRenderPixelPerfect", &View::setRenderPixelPerfect,
        "getPixel", &View::getPixel,
        "setPixel", &View::setPixel,
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
        "setFade", &Rect::setFade,
        "setThickness", &Rect::setThickness,
        sol::base_classes, sol::bases<Drawable>());
}

void UIScriptTypes::addLine() {
    auto lineFactory = sol::factories([&engine = engine](int fromX, int fromY, int toX, int toY) {
        std::unique_ptr<Line> line = std::make_unique<Line>(engine, fromX, fromY, toX, toY);
        return line;
        });
    lua.new_usertype<Line>("Line",
        sol::meta_function::construct, lineFactory,
        sol::call_constructor, lineFactory,
        sol::base_classes, sol::bases<Drawable, Rect>());
}

void UIScriptTypes::addCircle() {
    auto circleFactory = sol::factories([&engine = engine]() {
        std::unique_ptr<Circle> circle = std::make_unique<Circle>(engine);
        circle->setSize(100, 100);
        return circle;
        });
    lua.new_usertype<Circle>("Circle",
        sol::meta_function::construct, circleFactory,
        sol::call_constructor, circleFactory,
        "setFade", &Circle::setFade,
        "setThickness", &Circle::setThickness,
        sol::base_classes, sol::bases<Drawable>());
}


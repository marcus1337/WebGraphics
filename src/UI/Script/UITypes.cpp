#include "UITypes.h"
#include "UI/Widgets/Button.h"
#include "UI/Widgets/Slider.h"

UITypes::UITypes(sol::state& _lua, Engine& _engine) : lua(_lua), engine(_engine), graphics(_engine.graphics) {

}

void UITypes::setTypes() {
    addUIElement();
    addButton();
    addSlider();
    addTimer();
}

void UITypes::addUIElement() {
    lua.new_usertype<UIElement>("UIElement",
        "setActive", &UIElement::setActive,
        "setInactive", &UIElement::setInactive,
        "getX", &UIElement::getX,
        "getY", &UIElement::getY,
        "getWidth", &UIElement::getWidth,
        "getHeight", &UIElement::getHeight,
        "isHovered", &UIElement::isHovered,
        "isPressed", &UIElement::isPressed,
        "update", &UIElement::update,
        "render", &UIElement::render);
}

void UITypes::addButton() {
    auto btnFactory = sol::factories([&engine = engine](int pixelWidth, int pixelHeight) {
        std::unique_ptr<Button> btn = std::make_unique<Button>(engine, pixelWidth, pixelHeight);
        return btn; });
    lua.new_usertype<Button>("Button",
        sol::meta_function::construct, btnFactory,
        sol::call_constructor, btnFactory,
        "setPosition", &Button::setPosition,
        "setText", &Button::setText,
        "setImage", &Button::setImage,
        "paint", &Button::paint,
        "clearView", &Button::clearView,
        "onPressCallback", &Button::onPressCallback,
        sol::base_classes, sol::bases<UIElement>());
}

void UITypes::addSlider() {
    auto sliderFactory = sol::factories([&engine = engine](int pixelWidth, int pixelHeight) {
        std::unique_ptr<Slider> slider = std::make_unique<Slider>(engine, pixelWidth, pixelHeight);
        return slider; });
    lua.new_usertype<Slider>("Slider",
        sol::meta_function::construct, sliderFactory,
        sol::call_constructor, sliderFactory,
        "setPosition", &Slider::setPosition,
        "setValue", &Slider::setValue,
        "getValue", &Slider::getValue,
        "setBoxColor", &Slider::setBoxColor,
        "setLineColor", &Slider::setLineColor,
        "setMarkedLineColor", &Slider::setMarkedLineColor,
        "setBackgroundColor", &Slider::setBackgroundColor,
        "setBackgroundAlpha", &Slider::setBackgroundAlpha,
        "onValueChangeCallback", &Slider::onValueChangeCallback,
        sol::base_classes, sol::bases<UIElement>());
}

void UITypes::addTimer() {
    lua.new_usertype<Timer>("Timer",
        "getDeltaTimeMilliseconds", &Timer::getDeltaTimeMilliseconds,
        "getPassedMilliseconds", &Timer::getPassedMilliseconds,
        "getPassedTimeInterpolation", &Timer::getPassedTimeInterpolation,
        "getPassedTimeInterpolationCurve", &Timer::getPassedTimeInterpolationCurve);
}
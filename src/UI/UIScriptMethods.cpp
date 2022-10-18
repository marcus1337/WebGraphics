
#include "UIScriptMethods.h"
#include <tuple>

UIScriptMethods::UIScriptMethods(sol::state& _lua, Engine& _engine) : lua(_lua), engine(_engine), graphics(_engine.graphics) {

}

void UIScriptMethods::setMethods() {
    lua["isFullScreen"] = [&engine = engine]() {
        return engine.window.isFullScreen();
    };
    lua["setFullScreen"] = [&engine = engine](bool _fullScreen) {
#ifndef EMSCRIPTEN
        engine.window.setFullScreen(_fullScreen);
#else
        std::cout << "warning: setFullScreen() not implemented in Emscripten.\n";
#endif
    };

    lua["queueMusic"] = [&audio = engine.audio](std::string musicName, int maxQueueLimit) {
        audio.queueMusic(musicName, maxQueueLimit);
    };
    lua["queueEffect"] = [&audio = engine.audio](std::string effectName, int maxQueueLimit) {
        audio.queueEffect(effectName, maxQueueLimit);
    };

    lua["muteSound"] = [&audio = engine.audio]() {
        audio.muteSound();
    };
    lua["unmuteSound"] = [&audio = engine.audio]() {
        audio.unmuteSound();
    };
    lua["isSoundMuted"] = [&audio = engine.audio]() {
        return audio.isMuted();
    };
    lua["getMusicVolume"] = [&audio = engine.audio]() {
        return audio.getMusicVolume();
    };
    lua["setMusicVolume"] = [&audio = engine.audio](float volume) {
        audio.setMusicVolume(volume);
    };
    lua["getEffectVolume"] = [&audio = engine.audio]() {
        return audio.getEffectVolume();
    };
    lua["setEffectVolume"] = [&audio = engine.audio](float volume) {
        audio.setEffectVolume(volume);
    };
    lua["isMousePointerInside"] = [&engine = engine](int _x, int _y, int _width, int _height) {
        auto mousePos = engine.graphics.getPixelPosition(engine.window.mouse.x, engine.window.mouse.y);
        int mouseX = std::get<0>(mousePos);
        int mouseY = std::get<1>(mousePos);
        return mouseX >= _x && mouseX <= _x + _width && mouseY >= _y && mouseY <= _y + _height;
    };
    lua["isMousePress"] = [&mouse = engine.window.mouse]() {
        return mouse.isLeftPress;
    };
    lua["isMouseRelease"] = [&mouse = engine.window.mouse]() {
        return mouse.isLeftReleased;
    };
}
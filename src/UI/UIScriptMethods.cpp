
#include "UIScriptMethods.h"


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
    lua["isAudioInitialized"] = [&audio = engine.audio]() {
        return audio.isInitialized();
    };
    lua["setEffectVolume"] = [&audio = engine.audio](float volume) {
        audio.setEffectVolume(volume);
    };
}
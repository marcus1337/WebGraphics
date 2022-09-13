#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

#ifndef EMSCRIPTEN
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
SoLoud::Soloud soloud;
SoLoud::Wav wav;
#endif 

Audio::Audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cout << "Failed to load SDL_INIT\n";

#ifndef EMSCRIPTEN
    soloud.init();
    wav.load(getMusicFilePath("sample").c_str());
#endif 
}

Audio::~Audio() {
#ifndef EMSCRIPTEN
    soloud.deinit();
#endif 
    SDL_CloseAudio();
    SDL_Quit();
}

std::string Audio::getMusicFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "music//" + name + ".wav";
}

std::string Audio::getEffectFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "fx//" + name + ".wav";
}

void Audio::playMusic(std::string musicName) {
    std::string filePath = getMusicFilePath(musicName);
    std::cout << "playing: " << filePath << "\n";
#ifndef EMSCRIPTEN                    
     int handle1 = soloud.play(wav);           
     soloud.setVolume(handle1, 1.0f);           
#endif
}
void Audio::playEffect(std::string effectName) {

}
float Audio::getMusicVolume() {
    return 0.0f;
}
void Audio::setMusicVolume(float volumePercentage) {

}
float Audio::getEffectVolume() {
    return 0.0f;
}
void Audio::setEffectVolume(float volumePercentage) {

}
void Audio::muteSound() {

}
void Audio::unmuteSound() {

}

bool Audio::isMuted() {

    return muted;
}


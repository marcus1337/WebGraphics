#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
SoLoud::Soloud soloud;
SoLoud::Bus musicBus;
SoLoud::Bus effectBus;
std::map<std::string, SoLoud::Wav*> soundMap;
int musicBusHandle, effectBusHandle;

Audio::Audio() {
}

void Audio::init(){
    if(!inited){
        inited = true;
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
            std::cout << "Failed to load SDL_INIT\n";
        soloud.init();
        musicBusHandle = soloud.play(musicBus);
        effectBusHandle = soloud.play(effectBus);
    }
}

Audio::~Audio() {
    for (const auto& [key, value] : soundMap) {
        delete value;
    }
    soloud.deinit();
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
    init();
    std::string filePath = getMusicFilePath(musicName);
    std::cout << "Music: " << musicName << "\n";
    if (!soundMap.contains(musicName)) {
        SoLoud::Wav* wav = new  SoLoud::Wav();
        wav->load(getMusicFilePath(musicName).c_str());
        soundMap[musicName] = wav;
    }
    musicBus.play(*soundMap[musicName]);
}

void Audio::playEffect(std::string effectName) {
    init();
    std::string filePath = getEffectFilePath(effectName);
    std::cout << "Effect: " << effectName << "\n";
    if (!soundMap.contains(effectName)) {
        SoLoud::Wav* wav = new SoLoud::Wav();
        wav->load(getMusicFilePath(effectName).c_str());
        soundMap[effectName] = wav;
    }
    effectBus.play(*soundMap[effectName]);
}

float Audio::getMusicVolume() {
    return soloud.getVolume(musicBusHandle);
}

void Audio::setMusicVolume(float volumePercentage) {
    soloud.setVolume(musicBusHandle, volumePercentage);
}

float Audio::getEffectVolume() {
    return soloud.getVolume(effectBusHandle);
}

void Audio::setEffectVolume(float volumePercentage) {
    soloud.setVolume(effectBusHandle, volumePercentage);
}

void Audio::muteSound() {
    soloud.stopAll();
    muted = true;
}

void Audio::unmuteSound() {
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    muted = false;
}

bool Audio::isMuted() {
    return muted;
}

bool Audio::isInitialized() {
    return inited;
}
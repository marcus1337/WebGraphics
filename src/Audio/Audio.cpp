#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

Audio::Audio() {
}

SoLoud::Wav* Audio::getWavPointer(std::string name, std::string path) {
    init();
    std::cout << "Sound: " << name << "\n";
    if (!soundMap.contains(name)) {
        SoLoud::Wav* wav = new  SoLoud::Wav();
        wav->load(path.c_str());
        soundMap[name] = wav;
    }
    return soundMap[name];
}

void Audio::init(){
    if(!inited){
        std::cout << "initializing audio...\n";
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

SoLoud::Wav* Audio::getWavPointer(std::string name, SoundType soundType) {
    SoLoud::Wav* wavPtr = nullptr;
    if (soundType == SoundType::MUSIC)
        wavPtr = getWavPointer(name, getMusicFilePath(name));
    if (soundType == SoundType::FX)
        wavPtr = getWavPointer(name, getEffectFilePath(name));
    return wavPtr;
}

void Audio::queueMusic(std::string musicName, int maxQueueSize) {
    if (musicQueue.getQueueCount() < maxQueueSize) {
        musicBus.play(musicQueue);
        musicQueue.play(*getWavPointer(musicName, SoundType::MUSIC));
    }
}
void Audio::queueEffect(std::string effectName, int maxQueueSize) {
    if (effectQueue.getQueueCount() < maxQueueSize) {
        effectBus.play(effectQueue);
        effectQueue.play(*getWavPointer(effectName, SoundType::FX));
    }
}

std::string Audio::getMusicFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "music//" + name + ".wav";
}
std::string Audio::getEffectFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "fx//" + name + ".wav";
}

void Audio::playMusic(std::string musicName) {
    musicBus.play(*getWavPointer(musicName, SoundType::MUSIC));
}

void Audio::playEffect(std::string effectName) {
    effectBus.play(*getWavPointer(effectName, SoundType::FX));
}

float Audio::getMusicVolume() {
    init();
    return soloud.getVolume(musicBusHandle);
}

void Audio::setMusicVolume(float volumePercentage) {
    init();
    soloud.setVolume(musicBusHandle, volumePercentage);
    prevMusicVolume = volumePercentage;
}

float Audio::getEffectVolume() {
    init();
    return soloud.getVolume(effectBusHandle);
}

void Audio::setEffectVolume(float volumePercentage) {
    init();
    soloud.setVolume(effectBusHandle, volumePercentage);
    prevEffectVolume = volumePercentage;
}

void Audio::muteSound() {
    init();
    soloud.stopAll();
    muted = true;
}

void Audio::unmuteSound() {
    init();
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    effectBus.play(effectQueue);
    musicBus.play(musicQueue);
    setMusicVolume(prevMusicVolume);
    setEffectVolume(prevEffectVolume);
    muted = false;
}

bool Audio::isMuted() {
    return muted;
}

bool Audio::isInitialized() {
    return inited;
}
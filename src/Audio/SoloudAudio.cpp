#include "SoloudAudio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

SoloudAudio::SoloudAudio() {
}

SoLoud::Wav* SoloudAudio::getWavPointer(std::string name, std::string path) {
    std::cout << "Sound: " << name << "\n";
    if (!soundMap.contains(name)) {
        SoLoud::Wav* wav = new  SoLoud::Wav();
        wav->load(path.c_str());
        soundMap[name] = wav;
    }
    return soundMap[name];
}

void SoloudAudio::init() {
    std::cout << "initializing audio...\n";
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "Failed to load SDL_INIT\n";
        return;
    }
    soloud.init();
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    initialized = true;
}

SoloudAudio::~SoloudAudio() {
    for (const auto& [key, value] : soundMap) {
        delete value;
    }
    soloud.deinit();
    SDL_CloseAudio();
    SDL_Quit();
}

SoLoud::Wav* SoloudAudio::getWavPointer(std::string name, SoundType soundType) {
    SoLoud::Wav* wavPtr = nullptr;
    if (soundType == SoundType::MUSIC)
        wavPtr = getWavPointer(name, getMusicFilePath(name));
    if (soundType == SoundType::FX)
        wavPtr = getWavPointer(name, getEffectFilePath(name));
    return wavPtr;
}

void SoloudAudio::queueMusic(std::string musicName, int maxQueueSize) {
    if (musicQueue.getQueueCount() < maxQueueSize) {
        musicBus.play(musicQueue);
        musicQueue.play(*getWavPointer(musicName, SoundType::MUSIC));
    }
}
void SoloudAudio::queueEffect(std::string effectName, int maxQueueSize) {
    if (effectQueue.getQueueCount() < maxQueueSize) {
        effectBus.play(effectQueue);
        effectQueue.play(*getWavPointer(effectName, SoundType::FX));
    }
}

std::string SoloudAudio::getMusicFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "music//" + name + ".wav";
}
std::string SoloudAudio::getEffectFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "fx//" + name + ".wav";
}

void SoloudAudio::playMusic(std::string musicName) {
    musicBus.play(*getWavPointer(musicName, SoundType::MUSIC));
}

void SoloudAudio::playEffect(std::string effectName) {
    effectBus.play(*getWavPointer(effectName, SoundType::FX));
}

float SoloudAudio::getMusicVolume() {
    return soloud.getVolume(musicBusHandle);
}

void SoloudAudio::setMusicVolume(float volumePercentage) {
    soloud.setVolume(musicBusHandle, volumePercentage);
    prevMusicVolume = volumePercentage;
}

float SoloudAudio::getEffectVolume() {
    return soloud.getVolume(effectBusHandle);
}

void SoloudAudio::setEffectVolume(float volumePercentage) {
    soloud.setVolume(effectBusHandle, volumePercentage);
    prevEffectVolume = volumePercentage;
}

void SoloudAudio::muteSound() {
    soloud.stopAll();
    muted = true;
}

void SoloudAudio::unmuteSound() {
    musicBusHandle = soloud.play(musicBus);
    effectBusHandle = soloud.play(effectBus);
    effectBus.play(effectQueue);
    musicBus.play(musicQueue);
    setMusicVolume(prevMusicVolume);
    setEffectVolume(prevEffectVolume);
    muted = false;
}

bool SoloudAudio::isMuted() {
    return muted;
}

bool SoloudAudio::isInitialized() {
    return initialized;
}
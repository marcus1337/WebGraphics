#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
SoLoud::Soloud soloud;
SoLoud::Bus musicBus;
SoLoud::Bus effectBus;
SoLoud::Queue musicQueue;
SoLoud::Queue effectQueue;
std::map<std::string, SoLoud::Wav*> soundMap;

Audio::Audio() {
}

void* Audio::getWavPointer(std::string name, std::string path) {
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

void Audio::queueMusic(std::string musicName, int maxQueueSize) {
    if (musicQueue.getQueueCount() < maxQueueSize) {
        SoLoud::Wav* wavPtr = (SoLoud::Wav*)getWavPointer(musicName, getMusicFilePath(musicName));
        musicBus.play(musicQueue);
        musicQueue.play(*wavPtr);
    }
}
void Audio::queueEffect(std::string effectName, int maxQueueSize) {
    if (effectQueue.getQueueCount() < maxQueueSize) {
        SoLoud::Wav* wavPtr = (SoLoud::Wav*)getWavPointer(effectName, getEffectFilePath(effectName));
        effectBus.play(effectQueue);
        effectQueue.play(*wavPtr);
    }
}

std::string Audio::getMusicFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "music//" + name + ".wav";
}
std::string Audio::getEffectFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "fx//" + name + ".wav";
}

void Audio::playMusic(std::string musicName) {
    SoLoud::Wav* wavPtr = (SoLoud::Wav*) getWavPointer(musicName, getMusicFilePath(musicName));
    musicBus.play(*wavPtr);
}

void Audio::playEffect(std::string effectName) {
    SoLoud::Wav* wavPtr = (SoLoud::Wav* )getWavPointer(effectName, getEffectFilePath(effectName));
    effectBus.play(*wavPtr);
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
    effectBus.play(effectQueue);
    musicBus.play(musicQueue);
    muted = false;
}

bool Audio::isMuted() {
    return muted;
}

bool Audio::isInitialized() {
    return inited;
}
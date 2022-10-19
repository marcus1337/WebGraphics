#include "Audio.h"
#include <iostream>

Audio::Audio() {

}
Audio::~Audio() {

}

void Audio::playMusic(std::string musicName) {
    if (isMuted())
        return;
    audio.playMusic(musicName);
}
void Audio::playEffect(std::string effectName) {
    if (isMuted())
        return;
    audio.playEffect(effectName);
}
void Audio::queueMusic(std::string musicName, int maxQueueSize) {
    if (isMuted())
        return;
    audio.queueMusic(musicName, maxQueueSize);
}
void Audio::queueEffect(std::string effectName, int maxQueueSize) {
    if (isMuted())
        return;
    audio.queueEffect(effectName, maxQueueSize);
}
float Audio::getMusicVolume() {
    if (isMuted())
        return 0.0f;
    return audio.getMusicVolume();
}
void Audio::setMusicVolume(float volumePercentage) {
    if (isMuted())
        return;
    audio.setMusicVolume(volumePercentage);
}
float Audio::getEffectVolume() {
    if (isMuted())
        return 0.0f;
    return audio.getEffectVolume();
}
void Audio::setEffectVolume(float volumePercentage) {
    if (isMuted())
        return;
    audio.setEffectVolume(volumePercentage);
}
void Audio::muteSound() {
    if (isMuted())
        return;
    audio.muteSound();
}
void Audio::unmuteSound() {
    if (!audio.isInitialized())
        audio.init();
    if (audio.isMuted())
        audio.unmuteSound();
}
bool Audio::isMuted() {
    if (!audio.isInitialized())
        return true;
    return audio.isMuted();
}
#include <string>
#include <map>
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

    enum class SoundType {
        MUSIC = 0,
        FX
    };
    int musicBusHandle, effectBusHandle;

    std::string getMusicFilePath(std::string name);
    std::string getEffectFilePath(std::string name);
    bool muted = false;
    bool inited = false;
    SoLoud::Wav* getWavPointer(std::string name, std::string path);
    SoLoud::Wav* getWavPointer(std::string name, SoundType soundType);

    SoLoud::Soloud soloud;
    SoLoud::Bus musicBus;
    SoLoud::Bus effectBus;
    SoLoud::Queue musicQueue;
    SoLoud::Queue effectQueue;
    std::map<std::string, SoLoud::Wav*> soundMap;
public:
    void init();
    Audio();
    ~Audio();
    bool isInitialized();
    void playMusic(std::string musicName);
    void playEffect(std::string effectName);
    void queueMusic(std::string musicName, int maxQueueSize);
    void queueEffect(std::string effectName, int maxQueueSize);

    float getMusicVolume();
    void setMusicVolume(float volumePercentage);
    float getEffectVolume();
    void setEffectVolume(float volumePercentage);
    void muteSound();
    void unmuteSound();
    bool isMuted();

};

#endif
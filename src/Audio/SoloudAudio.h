#include <string>
#include <map>
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include <vector>

#ifndef SOLOUDAUDIO_H
#define SOLOUDAUDIO_H

class SoloudAudio {

    int musicBusHandle, effectBusHandle;
    float prevEffectVolume = 0.0f;
    float prevMusicVolume = 0.0f;

    bool muted = false;
    bool initialized = false;
    SoLoud::Wav* getWavPointer(std::string soundName);

    SoLoud::Soloud soloud;
    SoLoud::Bus musicBus;
    SoLoud::Bus effectBus;
    SoLoud::Queue musicQueue;
    SoLoud::Queue effectQueue;
    std::map<std::string, SoLoud::Wav*> soundMap;

public:

    void init();
    void loadSounds(std::vector<std::string> soundFilePaths, std::vector<std::string> soundNames);

    SoloudAudio();
    ~SoloudAudio();
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

#include <string>
#include <map>
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
#include "SoloudAudio.h"

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

    SoloudAudio audio;
    bool muted = true;

public:
    Audio();
    ~Audio();

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
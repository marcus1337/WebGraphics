#include <string>

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

    std::string getMusicFilePath(std::string name);
    std::string getEffectFilePath(std::string name);
    bool muted = false;

public:
    Audio();
    ~Audio();
    void playMusic(std::string musicName);
    void playEffect(std::string effectName);

    float getMusicVolume();
    void setMusicVolume(float volumePercentage);
    float getEffectVolume();
    void setEffectVolume(float volumePercentage);
    void muteSound();
    void unmuteSound();
    bool isMuted();

};

#endif
#include <string>
#include <map>

#ifndef AUDIO_H
#define AUDIO_H

class Audio {
    int musicBusHandle, effectBusHandle;

    std::string getMusicFilePath(std::string name);
    std::string getEffectFilePath(std::string name);
    bool muted = false;
    bool inited = false;
    void* getWavPointer(std::string name, std::string path);
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
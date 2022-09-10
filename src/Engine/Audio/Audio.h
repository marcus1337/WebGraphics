#include <string>

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

    std::string getMusicFilePath(std::string name);
    std::string getEffectFilePath(std::string name);

public:
    Audio();
    void playMusic(std::string musicName);
    void playEffect(std::string effectName);

};

#endif
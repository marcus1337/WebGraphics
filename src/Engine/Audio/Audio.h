#include <string>

#ifndef AUDIO_H
#define AUDIO_H

class Audio {

public:
    Audio();
    void playMusic(std::string musicName);
    void playEffect(std::string effectName);

};

#endif
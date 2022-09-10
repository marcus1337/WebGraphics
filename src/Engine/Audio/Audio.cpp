#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>
#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"

//SoLoud::Soloud soloud;
//SoLoud::Wav wav;

Audio::Audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cout << "Failed to load SDL_INIT\n";

    //soloud.init();

   // wav.load(getMusicFilePath("sample").c_str());
}

Audio::~Audio() {
   // soloud.deinit();
    SDL_CloseAudio();
    SDL_Quit();
}

std::string Audio::getMusicFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "music//" + name + ".wav";

}

std::string Audio::getEffectFilePath(std::string name) {
    return FolderPaths::getAudioPath() + "fx//" + name + ".wav";
}

void Audio::playMusic(std::string musicName) {
    std::string filePath = getMusicFilePath(musicName);
    std::cout << "playing: " << filePath << "\n";

   // wav.setLooping(1);                        
   // int handle1 = soloud.play(wav);           
   // soloud.setVolume(handle1, 0.5f);           
   // soloud.setPan(handle1, -0.2f);
   // soloud.setRelativePlaySpeed(handle1, 0.6f); 
}
void Audio::playEffect(std::string effectName) {

}
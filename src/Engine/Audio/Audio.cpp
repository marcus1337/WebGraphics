#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>
#include "soloud/soloud.h"
#include "soloud/soloud_speech.h"
#include "soloud/soloud_thread.h"
#include "soloud/soloud_openmpt.h"
#include "soloud/soloud_wav.h"

SoLoud::Soloud soloud;
SoLoud::Speech speech;
SoLoud::Wav wav;

Audio::Audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cout << "Failed to load SDL_INIT\n";

    speech.setText("1 2 3   1 2 3   Hello world. Welcome to So-Loud.");
    soloud.init();
    //soloud.play(speech);

    wav.load(getMusicFilePath("sample").c_str());
    wav.setLooping(1);                        
    int handle1 = soloud.play(wav);           
    soloud.setVolume(handle1, 0.5f);           
    soloud.setPan(handle1, -0.2f);
    soloud.setRelativePlaySpeed(handle1, 0.6f); 
}

Audio::~Audio() {
    soloud.deinit();
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
}
void Audio::playEffect(std::string effectName) {

}
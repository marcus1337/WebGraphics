#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

Audio::Audio() {

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
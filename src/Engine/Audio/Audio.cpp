#include "Audio.h"
#include <IO/Files/FolderPaths.h>
#include <iostream>

#include <SDL2/SDL.h>

Uint32 wav_length; // length of our sample
Uint8* wav_buffer; // buffer containing our audio file
SDL_AudioSpec wav_spec;

Uint8* audio_pos; // global pointer to the audio buffer to be played
Uint32 audio_len; // remaining length of the sample we have to play

void my_audio_callback(void* userdata, Uint8* stream, int len) {

	if (audio_len == 0)
		return;

    std::cout << "len " << len << "\n";
	len = (len > audio_len ? audio_len : len);
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other

	audio_pos += len;
	audio_len -= len;
    std::cout << "left: " << audio_len << "\n";
}

Audio::Audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        std::cout << "Failed to load SDL_INIT\n";

    if (SDL_LoadWAV(getMusicFilePath("sample").c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
        return;
    }

    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;
    // set our global static variables
    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length

    if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
        fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_PauseAudio(0);

}

Audio::~Audio() {
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
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
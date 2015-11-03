/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLMusic.h"

Diamond::SDLMusic::SDLMusic(Mix_Music *music) : music(music), loop(-1) {
}

void Diamond::SDLMusic::play() {
	Mix_PlayMusic(music, loop);
}

void Diamond::SDLMusic::pause() {
	Mix_PauseMusic();
}

void Diamond::SDLMusic::resume() {
	Mix_ResumeMusic();
}

void Diamond::SDLMusic::stop() {
	Mix_HaltMusic();
}

void Diamond::SDLMusic::set_loop(bool loop) {
	loop ? this->loop = -1 : this->loop = 1;
}

int Diamond::SDLMusic::get_volume() {
	return Mix_VolumeMusic(-1);
}

void Diamond::SDLMusic::set_volume(int volume) {
	Mix_VolumeMusic(volume);
}

Diamond::SDLMusic::~SDLMusic() {
	Mix_FreeMusic(music);
}

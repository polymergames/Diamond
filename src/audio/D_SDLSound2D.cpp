/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLSound2D.h"

Diamond::SDLSound2D::SDLSound2D(Mix_Chunk *sound) : sound(sound), channel(0) {
}

void Diamond::SDLSound2D::play() {
	channel = Mix_PlayChannel(-1, sound, 0);
}

void Diamond::SDLSound2D::pause() {
	Mix_Pause(channel);
}

void Diamond::SDLSound2D::resume() {
	Mix_Resume(channel);
}

void Diamond::SDLSound2D::stop() {
	Mix_HaltChannel(channel);
}

int Diamond::SDLSound2D::get_volume() const {
	return Mix_VolumeChunk(sound, -1);
}

void Diamond::SDLSound2D::set_volume(int volume) {
	Mix_VolumeChunk(sound, volume);
}

Diamond::SDLSound2D::~SDLSound2D() {
	Mix_FreeChunk(sound);
}

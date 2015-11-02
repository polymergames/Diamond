/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLSound2D.h"

Diamond::SDLSound2D::SDLSound2D(Mix_Chunk *sound) : sound(sound) {
}

void Diamond::SDLSound2D::play() {
	//
}

Diamond::SDLSound2D::~SDLSound2D() {
	Mix_FreeChunk(sound);
}

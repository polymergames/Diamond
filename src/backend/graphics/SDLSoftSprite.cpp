/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLSoftSprite.h"

Diamond::SDLSoftSprite::SDLSoftSprite(SDL_Surface *surface) : surface(surface) {}

Diamond::SDLSoftSprite::SDLSoftSprite(std::string img) : surface(nullptr) {
	// TODO: Handle what happens if image loading fails. USE resource manager!
	SDLSoftSprite::surface = SDL_LoadBMP(img.c_str());
}

SDL_Surface *Diamond::SDLSoftSprite::get_surface() {
	return surface;
}

Diamond::SDLSoftSprite::~SDLSoftSprite() {
	SDL_FreeSurface(surface);
}

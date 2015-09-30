/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLSurface.h"

Diamond::SDLSurface::SDLSurface(SDL_Surface *surface) : surface(surface) {}

Diamond::SDLSurface::SDLSurface(std::string img) : surface(nullptr) {
	// TODO: Handle what happens if image loading fails. USE resource manager!
	SDLSurface::surface = SDL_LoadBMP(img.c_str());
}

SDL_Surface *Diamond::SDLSurface::get_surface() {
	return surface;
}

Diamond::SDLSurface::~SDLSurface() {
	SDL_FreeSurface(surface);
}

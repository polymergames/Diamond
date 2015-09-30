/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDLSURFACE_H
#define SDLSURFACE_H

#include <iostream>
#include <memory>
#include "SDL.h"
#include "SoftSprite.h"

namespace Diamond {

	/**
	 The SDL implementation of a SoftSprite, which is a software-rendered sprite..
	*/
	class SDLSurface : public SoftSprite {
		public:
		SDLSurface(SDL_Surface *surface);
		SDLSurface(std::string img);

		SDL_Surface *get_surface();

		~SDLSurface();

		private:
		SDL_Surface *surface;
	};
}

#endif // SPRITE_H

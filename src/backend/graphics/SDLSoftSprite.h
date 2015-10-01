/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_SOFT_SPRITE_H
#define SDL_SOFT_SPRITE_H

#include <iostream>
#include <memory>
#include "SDL.h"
#include "SoftSprite.h"

namespace Diamond {

	/**
	 The SDL implementation of a SoftSprite, which is a software-rendered sprite.
	*/
	class SDLSoftSprite : public SoftSprite {
		public:
		SDLSoftSprite(SDL_Surface *surface);
		SDLSoftSprite(std::string img);

		SDL_Surface *get_surface();

		~SDLSoftSprite();

		private:
		SDL_Surface *surface;
	};
}

#endif // SDL_SOFT_SPRITE_H

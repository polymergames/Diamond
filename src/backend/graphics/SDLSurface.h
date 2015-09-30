/*
Copyright (c) 2015 Polymer Games
*/

#ifndef SDLSURFACE_H
#define SDLSURFACE_H

#include <iostream>
#include "SDL.h"
#include "SoftSprite.h"

namespace Diamond {
	class SDLSurface : public SoftSprite {
		public:
		SDLSurface(SDL_Surface *surface);
		SDLSurface(std::string img);
		~SDLSurface();

		private:
		SDL_Surface *surface;
	};
}

#endif // SPRITE_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include "Texture.h"
#include "SDL.h"

namespace Diamond {
	class SDLTexture : public Texture {
		public:
		SDLTexture();
		SDLTexture(SDL_Texture *texture);

		SDL_Texture *texture;

		~SDLTexture();
	};
}

#endif // SDL_TEXTURE_H

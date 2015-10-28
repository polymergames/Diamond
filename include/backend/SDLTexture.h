/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <memory>
#include "Texture.h"
#include "SDL.h"

namespace Diamond {
	class SDLTexture : public Texture {
		public:
		SDLTexture(SDL_Texture *texture, int width, int height);

		void set_color(RGBA color);

		~SDLTexture();

		SDL_Texture *texture;
	};
}

#endif // SDL_TEXTURE_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_TEXTURE_H
#define D_SDL_TEXTURE_H

#include "SDL.h"

#include "D_Texture.h"

namespace Diamond {
	class SDLTexture : public Texture {
		public:
		SDLTexture(SDL_Texture *texture, int width, int height);

		void set_color(RGBA color);

		~SDLTexture();

		SDL_Texture *texture;
	};
}

#endif // D_SDL_TEXTURE_H

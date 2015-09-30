/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <iostream>
#include <memory>
#include "Launcher.h"
#include "Renderer.h"
#include "SDL.h"
#include "SDLSurface.h"

namespace Diamond {
	class SDLRenderer : public Renderer {
		public:
		SDLRenderer(Config &config);

		SoftSprite *gen_soft_sprite(std::string img);

		int blit_soft_sprite(SoftSprite &src);

		int blit_soft_sprite(SoftSprite &src, SoftSprite &dest);

		~SDLRenderer();

		private:
		SDL_Window *window;
		SDL_Surface *screen_surface;

		SDL_Window *create_window(std::string name, int window_width, int window_height);
	};
}

#endif // SDL_RENDERER_H

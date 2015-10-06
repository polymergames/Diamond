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

namespace Diamond {
	class SDLRenderer : public Renderer {
		public:
		SDLRenderer(Config &config);

		void render();

		~SDLRenderer();

		private:
		SDL_Window *window;
		SDL_Event e;

		void render_graphics();
	};
}

#endif // SDL_RENDERER_H

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
		~SDLRenderer();

		private:
		SDL_Window *window = nullptr;

		void create_window(std::string name, int window_width, int window_height);
	};
}

#endif // SDL_RENDERER_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <iostream>
#include <memory>
#include "Renderer.h"
#include "SDL.h"

namespace Diamond {
	class SDLRenderer : public Renderer {
		public:
		SDLRenderer(std::string name, int window_width, int window_height);
		~SDLRenderer();

		private:
		std::shared_ptr<SDL_Window> window = nullptr;
	};
}

#endif // SDL_RENDERER_H

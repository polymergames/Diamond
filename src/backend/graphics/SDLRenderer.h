/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <iostream>
#include <memory>
#include "Renderer2D.h"
#include "SDL.h"

namespace Diamond {
	struct Config;

	class SDLRenderer : public Renderer2D {
		public:
		SDLRenderer();
		
		/**
		 Initializes SDL and creates window.
		*/
		bool init(Config &config);

		/**
		 Called in main rendering loop.
		*/
		void render();

		/**
		 Destroys window and shuts down SDL.
		*/
		~SDLRenderer();

		private:
		SDL_Window *window;
		SDL_Event e;

		void render_graphics();
	};
}

#endif // SDL_RENDERER_H

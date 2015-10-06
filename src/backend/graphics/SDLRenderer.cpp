/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer.h"

/*
 Initializes SDL and creates window.
*/
Diamond::SDLRenderer::SDLRenderer(Config &config) : window(nullptr) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow(config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.window_width, config.window_height, 
			config.window_width <=0 || config.window_height <=0 ? SDL_WINDOW_FULLSCREEN : 0);
		if (window == nullptr) {
			// TODO: Handle window creation failure
			std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
		}
	}
}

/*
 Destroys window and shuts down SDL.
*/
Diamond::SDLRenderer::~SDLRenderer() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*** Private functions ***/

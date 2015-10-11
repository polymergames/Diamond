/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer2D.h"
#include "Launcher.h"
#include "SDLInput.h"

Diamond::SDLRenderer2D::SDLRenderer2D() : window(nullptr) {}

bool Diamond::SDLRenderer2D::init(Config &config) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure and log
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		window = SDL_CreateWindow(config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.window_width, config.window_height,
			config.window_width <= 0 || config.window_height <= 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		if (window == nullptr) {
			// TODO: Handle window creation failure and log
			std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	return true;
}

void Diamond::SDLRenderer2D::render() {
	// Handle SDL events
    Input::reset();
	while (SDL_PollEvent(&e)) {
        SDLInput::handle(e);
	}

	// Render all the graphics
	render_graphics();

	// Update window
	SDL_UpdateWindowSurface(window);
}

Diamond::SDLRenderer2D::~SDLRenderer2D() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}


/*** Private functions ***/

void Diamond::SDLRenderer2D::render_graphics() {
	// TODO
}

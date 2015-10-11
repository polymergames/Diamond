/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer2D.h"
#include <iostream>
#include "SDL_image.h"
#include "SDLInput.h"
#include "Launcher.h"

Diamond::SDLRenderer2D::SDLRenderer2D() : window(nullptr), renderer(nullptr) {}

bool Diamond::SDLRenderer2D::init(Config &config) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure and log
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create window
	window = SDL_CreateWindow(config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		config.window_width, config.window_height, config.window_width <= 0 || config.window_height <= 0 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	if (window == nullptr) {
		// TODO: Handle window creation failure and log
		std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		// TODO: Handle renderer creation failure and log
		std::cout << "SDL failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);

	// Initialize image loading
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if (IMG_Init(img_flags) != img_flags) {
		// TODO: Handle image-loader initialization failure and log
		std::cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
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
	IMG_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}


/*** Private functions ***/

void Diamond::SDLRenderer2D::render_graphics() {
	// TODO
}

/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer2D.h"
#include <iostream>
#include "SDL_image.h"
#include "SDLInput.h"

int Diamond::SDLRenderer2D::reserve_size = 10;

Diamond::SDLRenderer2D::SDLRenderer2D() : window(nullptr), renderer(nullptr) {
	render_objects.reserve(reserve_size);
}

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

	// Update window. TODO: Change to texture update instead of surface
	SDL_UpdateWindowSurface(window);
}

void Diamond::SDLRenderer2D::gen_render_obj(GameObject2D *parent, Texture *texture, Transform2 &transform) {
	int size = render_objects.size();
	if (size == render_objects.capacity()) {
		// Reallocate render_objects vector then loop through and reset their parents' references
		// This is done to maintain integrity of render pointers
		render_objects.reserve(size + reserve_size);
		for (std::vector<SDLRenderObj2D>::iterator i = render_objects.begin(); i != render_objects.end(); i++) {
			i->arm_parent();
		}
	}
	render_objects.push_back(SDLRenderObj2D(parent, texture, transform));
	render_objects[size].index = size;
}

void Diamond::SDLRenderer2D::destroy_render_obj(int index) {
	if (index < render_objects.size() - 1) { // If in middle of vector, replace it with the last render object in vector
		render_objects[index] = render_objects.back();
		render_objects[index].arm_parent();
		render_objects[index].index = index;
	}
	render_objects.pop_back();
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

/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer.h"

Diamond::SDLRenderer::SDLRenderer(Config &config) : window(nullptr), screen_surface(nullptr) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
	}
	else {
		window = create_window(config.game_name, config.window_width, config.window_height);
		if (window == nullptr) {
			// TODO: Handle window creation failure
		}
	}
}

Diamond::SoftSprite *Diamond::SDLRenderer::gen_soft_sprite(std::string img) {
	return new SDLSurface(img);
}

Diamond::SDLRenderer::~SDLRenderer() {
	// cleanup code
}


/*** Private functions ***/

SDL_Window *Diamond::SDLRenderer::create_window(std::string name, int window_width, int window_height) {
	return SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
}



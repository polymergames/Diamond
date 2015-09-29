/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer.h"

Diamond::SDLRenderer::SDLRenderer(Config &config) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
	}
	else {
		create_window(config.game_name, config.window_width, config.window_height);
	}
}

void Diamond::SDLRenderer::create_window(std::string name, int window_width, int window_height) {
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		// TODO: Handle window creation failure
	}
}

Diamond::SDLRenderer::~SDLRenderer() {
	// cleanup code
}

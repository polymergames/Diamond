/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer.h"

Diamond::SDLRenderer::SDLRenderer(std::string name, int window_width, int window_height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
	}
	else {
		window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_height, window_width, SDL_WINDOW_SHOWN));
	}
}

Diamond::SDLRenderer::~SDLRenderer() {
	// cleanup code
}

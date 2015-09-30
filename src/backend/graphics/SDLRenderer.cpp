/*
 Copyright (c) 2015 Polymer Games
*/

#include "SDLRenderer.h"

/*
 Initializes SDL and creates window.
*/
Diamond::SDLRenderer::SDLRenderer(Config &config) : window(nullptr), screen_surface(nullptr) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
	}
	else {
		window = create_window(config.game_name, config.window_width, config.window_height);
		if (window == nullptr) {
			// TODO: Handle window creation failure
		}
		else if (config.software_render) {
			screen_surface = SDL_GetWindowSurface(window);
		}
	}
}

Diamond::SoftSprite *Diamond::SDLRenderer::gen_soft_sprite(std::string img) {
	return new SDLSurface(img);
}

int Diamond::SDLRenderer::blit_soft_sprite(Diamond::SoftSprite &src) {
	return SDL_BlitSurface(dynamic_cast<Diamond::SDLSurface&>(src).get_surface(), nullptr, screen_surface, nullptr);
}

int Diamond::SDLRenderer::blit_soft_sprite(Diamond::SoftSprite &src, Diamond::SoftSprite &dest) {
	return SDL_BlitSurface(dynamic_cast<Diamond::SDLSurface&>(src).get_surface(), nullptr, dynamic_cast<Diamond::SDLSurface&>(dest).get_surface(), nullptr);
}

/*
 Destroys window and shuts down SDL.
*/
Diamond::SDLRenderer::~SDLRenderer() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}


/*** Private functions ***/

SDL_Window *Diamond::SDLRenderer::create_window(std::string name, int window_width, int window_height) {
	return SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
}

/*
 Copyright (c) 2015 Polymer Games
*/

#include "GLWinRenderer2D.h"

Diamond::GLWinRenderer2D::GLWinRenderer2D(Config &config) : window(nullptr) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// TODO: Handle initialization failure
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow(config.game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config.window_width, config.window_height, SDL_WINDOW_OPENGL);
		if (window == nullptr) {
			// TODO: Handle window creation failure
			std::cout << "SDL failed to create window! SDL Error: " << SDL_GetError() << std::endl;
		}
		else {
			context = SDL_GL_CreateContext(window);
		}
	}
}

Diamond::GLWinRenderer2D::~GLWinRenderer2D() {
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}

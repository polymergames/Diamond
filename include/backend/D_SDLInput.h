/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_INPUT_H
#define D_SDL_INPUT_H

#include "SDL.h"

#include "D_Input.h"

namespace Diamond {
	namespace SDLInput {
		void handle(SDL_Event &e);
	}
}

#endif // D_SDL_INPUT_H

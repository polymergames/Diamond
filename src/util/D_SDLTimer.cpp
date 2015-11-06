/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLTimer.h"

#include "SDL.h"

uint32_t Diamond::SDLTimer::ms_elapsed() {
	return SDL_GetTicks();
}

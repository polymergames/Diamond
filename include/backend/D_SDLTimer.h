/*
 Copyright (c) 2015 Polymer Games
 */

#ifndef D_SDL_TIMER_H
#define D_SDL_TIMER_H

#include "D_Timer.h"

namespace Diamond {
	class SDLTimer : public Timer {
		public:
		uint32_t ms_elapsed() override;
	};
}

#endif // D_SDL_TIMER_H
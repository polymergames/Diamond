/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TIME_H
#define D_TIME_H

#include <stdint.h>

namespace Diamond {
	class Timer;
	namespace Time {
		
		extern float fps;

		/**
		 Returns the number of milliseconds elapsed since the game was launched.
		*/
		uint32_t msElapsed();

		/**
		 Called by Diamond launcher to set the platform-specific timing implementation.
		*/
		void setTimer(Timer *timer);
	};
}

#endif // D_TIME_H

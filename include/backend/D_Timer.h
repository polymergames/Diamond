/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TIMER_H
#define D_TIMER_H

#include <stdint.h>

namespace Diamond {
	class Timer {
		public:

		virtual uint32_t msElapsed() = 0;

		~Timer() {};
	};
}

#endif // D_TIMER_H

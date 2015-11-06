/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TIMER_H
#define D_TIMER_H

namespace Diamond {
	class Timer {
		public:

		virtual float seconds_since_start() = 0;

		~Timer() {};
	};
}

#endif // D_TIMER_H

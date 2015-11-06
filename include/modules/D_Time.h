/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TIME_H
#define D_TIME_H

namespace Diamond {
	class Timer;
	namespace Time {

		float seconds_since_start();

		// Do not call unless you know what you're doing!
		void set_timer(Timer *timer);
	};
}

#endif // D_TIME_H

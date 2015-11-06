/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TIME_H
#define D_TIME_H

namespace Diamond {
	class Timer;
	namespace Time {

		float seconds_since_start();

		/**
		 Called by Diamond launcher to set the platform-specific timing implementation.
		*/
		void set_timer(Timer *timer);
	};
}

#endif // D_TIME_H

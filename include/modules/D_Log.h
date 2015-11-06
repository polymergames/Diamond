/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LOG_H
#define D_LOG_H

namespace Diamond {
	class Logger;
	namespace Log {
		
		/**
		 Called by Diamond launcher to set the platform-specific logging implementation.
		*/
		void set_logger(Logger *logger);
		
	};
}

#endif // D_LOG_H

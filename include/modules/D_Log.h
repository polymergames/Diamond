/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LOG_H
#define D_LOG_H

namespace Diamond {
	class Logger;
	namespace Log {
		
		// Don't call unless you know what you're doing!
		void set_logger(Logger *logger);
		
	};
}

#endif // D_LOG_H

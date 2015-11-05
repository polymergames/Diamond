/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LOG_H
#define D_LOG_H

#include <memory>

#include "D_Logger.h"

namespace Diamond {
	namespace Log {
		
		// Don't call unless you know what you're doing!
		void set_logger(Logger *logger);
		
	};
}

#endif // D_LOG_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_DESKTOP_LOGGER_H
#define D_DESKTOP_LOGGER_H

#include "D_Logger.h"

namespace Diamond {
	class DesktopLogger : public Logger {
		public:
		DesktopLogger();
		~DesktopLogger();
	};
}

#endif // D_DESKTOP_LOGGER_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef DESKTOP_LOGGER_H
#define DESKTOP_LOGGER_H

#include "Logger.h"

namespace Diamond {
	class DesktopLogger : public Logger {
		public:
		DesktopLogger();
		~DesktopLogger();
	};
}

#endif // DESKTOP_LOGGER_H

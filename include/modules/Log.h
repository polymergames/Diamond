/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LOG_H
#define D_LOG_H

#include <memory>

namespace Diamond {
	class Logger;

	class Log {
		public:
		static void setLogger(Logger *logger);

		private:
		static std::unique_ptr<Logger> logger;
	};
}

#endif // D_LOG_H

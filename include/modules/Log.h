/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LOG_H
#define LOG_H

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

#endif // LOG_H

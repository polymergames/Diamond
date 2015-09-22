/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>

class Logger {
	public:
	static void setLogger(std::unique_ptr<Logger> logger);

	private:
	static std::unique_ptr<Logger> logger;
};

#endif // LOGGER_H

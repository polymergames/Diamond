/*
 Copyright (c) 2015 Polymer Games
*/

#include "Logger.h"

std::unique_ptr<Logger> Logger::logger;

void Logger::setLogger(std::unique_ptr<Logger> logger) {
	Logger::logger = std::move(logger);
}

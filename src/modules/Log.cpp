/*
 Copyright (c) 2015 Polymer Games
*/

#include "Log.h"
#include "Logger.h"

std::unique_ptr<Diamond::Logger> Diamond::Log::logger = nullptr;

void Diamond::Log::setLogger(Logger *logger) {
	Log::logger = std::unique_ptr<Logger>(logger);
}

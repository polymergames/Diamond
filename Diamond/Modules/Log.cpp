/*
 Copyright (c) 2015 Polymer Games
*/

#include "Log.h"

std::unique_ptr<Logger> Log::logger = nullptr;

void Log::setLogger(std::unique_ptr<Logger> logger) {
	Log::logger = std::move(logger);
}

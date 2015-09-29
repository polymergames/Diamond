/*
 Copyright (c) 2015 Polymer Games
*/

#include "Log.h"
using namespace Diamond;

std::unique_ptr<Logger> Diamond::Log::logger = nullptr;

void Diamond::Log::setLogger(Logger *logger) {
	Diamond::Log::logger = std::unique_ptr<Logger>(logger);
}

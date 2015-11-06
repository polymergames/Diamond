/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Log.h"

#include <memory>

#include "D_Logger.h"

namespace Diamond {
	namespace Log {
		static std::unique_ptr<Logger> logger = nullptr;
	}
}

void Diamond::Log::set_logger(Logger *logger) {
	if (Log::logger == nullptr && logger != nullptr)
		Log::logger = std::unique_ptr<Logger>(logger);
}

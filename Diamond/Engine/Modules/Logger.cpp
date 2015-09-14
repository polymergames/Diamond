/*
 Copyright (c) 2015 Polymer Games
 */
#include "Logger.h"

Logger Logger::*logger = nullptr;

void Logger::setLogger(Logger *logger)
{
	if (Logger::logger == nullptr && logger != nullptr)
		Logger::logger = logger;
}

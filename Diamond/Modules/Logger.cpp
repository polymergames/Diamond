/*
 Copyright (c) 2015 Polymer Games
 */

#include "Logger.h"

Logger Logger::*logger = nullptr;

void Logger::setLogger(Logger *logger)
{
	Logger::logger = logger;
}
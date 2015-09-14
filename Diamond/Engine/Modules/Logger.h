/*
 Copyright (c) 2015 Polymer Games
 */
#pragma once
class Logger
{
	public:
	static void setLogger(Logger *logger);

	private:
	static Logger *logger;
};

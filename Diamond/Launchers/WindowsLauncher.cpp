/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"

WindowsLauncher::WindowsLauncher() {
	Graphics::setRenderer(std::move(std::unique_ptr<SDLRenderer>(new SDLRenderer)));
	Log::setLogger(std::move(std::unique_ptr<Desktop_Logger>(new Desktop_Logger)));
}

WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

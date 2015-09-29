/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"
using namespace Diamond;

Diamond::WindowsLauncher::WindowsLauncher() {
	Graphics::setRenderer(std::move(std::unique_ptr<SDLRenderer>(new SDLRenderer)));
	Log::setLogger(std::move(std::unique_ptr<DesktopLogger>(new DesktopLogger)));
}

Diamond::WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

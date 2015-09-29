/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"
using namespace Diamond;

Diamond::WindowsLauncher::WindowsLauncher(Config &config) {
	Graphics::setRenderer(new SDLRenderer(config));
	Log::setLogger(new DesktopLogger());
}

Diamond::WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

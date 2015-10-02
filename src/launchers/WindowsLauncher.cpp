/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"

void Diamond::WindowsLauncher::init_engine(Config &config) {
	Diamond::Graphics::setRenderer(new SDLRenderer(config));
	Diamond::Log::setLogger(new DesktopLogger());
}

Diamond::WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

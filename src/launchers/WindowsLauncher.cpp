/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"
using namespace Diamond;

Diamond::WindowsLauncher::WindowsLauncher(Config &config) {
	Graphics::setRenderer(new SDLRenderer(config.game_name, config.window_height, config.window_width));
	Log::setLogger(new DesktopLogger());
}

Diamond::WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

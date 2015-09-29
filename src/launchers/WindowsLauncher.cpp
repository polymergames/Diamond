/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"
using namespace Diamond;

Diamond::WindowsLauncher::WindowsLauncher(Config &config) {
	Graphics::setRenderer(std::move(std::make_unique<SDLRenderer>(new SDLRenderer(config.game_name, config.window_height, config.window_width))));
	Log::setLogger(std::move(std::make_unique<DesktopLogger>(new DesktopLogger())));
}

Diamond::WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

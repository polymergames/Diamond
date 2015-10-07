/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "DesktopLogger.h"
#include "SDLRenderer.h"

bool Diamond::Launcher::is_open = true;

void Diamond::Launcher::init_win32(Config &config) {
	Diamond::Graphics::setRenderer(new SDLRenderer());
	if (!Graphics::init_renderer(config)) {
		// TODO: Handle render initialization failure
	}
	Diamond::Log::setLogger(new DesktopLogger());
}

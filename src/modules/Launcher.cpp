/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "DesktopLogger.h"
#include "SDLRenderer2D.h"

bool Diamond::Launcher::is_open = true;
struct Diamond::Config Diamond::Launcher::config = Diamond::Config();

void Diamond::Launcher::init_win32() {
	Diamond::Graphics2D::setRenderer(new SDLRenderer2D());
	if (!Graphics2D::init_renderer()) {
		// TODO: Handle render initialization failure
	}
	Diamond::Log::setLogger(new DesktopLogger());
}

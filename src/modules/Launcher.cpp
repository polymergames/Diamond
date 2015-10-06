/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"

bool Diamond::Launcher::is_open = true;

void Diamond::Launcher::init_win32(Config &config) {
	Diamond::Graphics::setRenderer(new SDLRenderer(config));
	Diamond::Log::setLogger(new DesktopLogger());
}

Diamond::Launcher::~Launcher() {
}

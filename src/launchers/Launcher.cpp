/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "WindowsLauncher.h"

std::unique_ptr<Diamond::Launcher> Diamond::Launcher::launcher;

void Diamond::Launcher::launch(Diamond::Config &config) {
#if defined ANDROID
	// Android launcher
#elif defined IOS
	// IOS launcher
#elif defined OSX
	// OSX launcher
#else
	Diamond::Launcher::launcher = std::unique_ptr<Diamond::WindowsLauncher>(new Diamond::WindowsLauncher(config));
#endif
}

Diamond::Launcher::~Launcher() {
}

/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "WindowsLauncher.h"
using namespace Diamond;

std::unique_ptr<Launcher> Diamond::Launcher::launcher;

void Diamond::Launcher::launch() {
#if defined ANDROID
	// Android launcher
#elif defined IOS
	// IOS launcher
#elif defined OSX
	// OSX launcher
#else
	launcher = std::unique_ptr<Launcher>(new WindowsLauncher());
#endif
}

Diamond::Launcher::~Launcher() {
}

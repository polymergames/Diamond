/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "WindowsLauncher.h"

std::unique_ptr<Launcher> Launcher::launcher;

void Launcher::launch() {
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

Launcher::~Launcher() {
}

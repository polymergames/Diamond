/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef WINDOWS_LAUNCHER_H
#define WINDOWS_LAUNCHER_H

#include "Launcher.h"
#include "Graphics.h"
#include "SDLRenderer.h"
#include "Log.h"
#include "DesktopLogger.h"

namespace Diamond {
	class WindowsLauncher : public Launcher {
		public:
		WindowsLauncher(Config &config);
		~WindowsLauncher();
	};
}

#endif // WINDOWS_LAUNCHER_H 

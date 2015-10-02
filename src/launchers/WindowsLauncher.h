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
		template <class Initialize, class DeltaUpdate> WindowsLauncher(Config &config, Initialize init, DeltaUpdate update);
		~WindowsLauncher();

		private:
		void init_engine(Config &config);
	};
}

template <class Initialize, class DeltaUpdate> Diamond::WindowsLauncher::WindowsLauncher(Diamond::Config &config, Initialize init, DeltaUpdate update) {
	// Init engine
	init_engine(config);

	// Init game
	init();

	// Update
	while (Diamond::Launcher::is_open) {
		update(1.0f); // TESTING
	}
}

#endif // WINDOWS_LAUNCHER_H 

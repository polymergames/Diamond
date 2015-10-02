/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>

namespace Diamond {
	struct Config {
		std::string game_name = "Pong";
		int window_width = 1280;
		int window_height = 720;
		bool software_render = false;
	};

	class Launcher {
		public:
		static int is_open; // TESTING

		/*
		 Call only once, at beginning of game!
		 init should define its operator with no arguments and void return type.
		 update should define its operator with one float argument (delta time) and void return type.
		*/
		template <class Initialize, class DeltaUpdate> static void launch(Config &config, Initialize init, DeltaUpdate update);

		virtual ~Launcher();

		private:
		static std::unique_ptr<Launcher> launcher;
	};
}

#include "WindowsLauncher.h"

template <class Initialize, class DeltaUpdate> static void Diamond::Launcher::launch(Diamond::Config &config, Initialize init, DeltaUpdate update) {
#if defined ANDROID
	// Android launcher
#elif defined IOS
	// IOS launcher
#elif defined OSX
	// OSX launcher
#else
	Diamond::Launcher::launcher = std::unique_ptr<Diamond::WindowsLauncher>(new Diamond::WindowsLauncher(config, init, update));
#endif
}

#endif // LAUNCHER_H

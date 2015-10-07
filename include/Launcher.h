/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>
#include "Graphics.h"
#include "Log.h"

namespace Diamond {
	struct Config {
		std::string game_name = "Pong";
		int window_width = 1280;
		int window_height = 720;
	};

	class Launcher {
		public:
		static bool is_open; // TESTING

		/**
		 Call only once, at beginning of game!
		 init should define its operator with no arguments and void return type.
		 update should define its operator with one float argument (delta time) and void return type.
		*/
		template <class Initialize, class DeltaUpdate> static void launch(Config &config, Initialize init, DeltaUpdate update);

		private:
		static void init_win32(Config &config);
	};
}

#include "Launcher.hpp" // Template implementation

#endif // LAUNCHER_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>
#include "Config.h"
#include "Graphics.h"
#include "Log.h"

namespace Diamond {
	class Launcher {
		public:
		static bool is_open;

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

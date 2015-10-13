/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>
#include "Config.h"
#include "Graphics2D.h"
#include "Log.h"

namespace Diamond {
	class Launcher {
		public:
		static bool is_open;
        
        static struct Config config;

		/**
		 Call only once, at beginning of game!
		 init should define its operator with no arguments and void return type.
		 update should define its operator with one float argument (delta time) and void return type.
		*/
		template <class Initialize, class DeltaUpdate> static void launch(Initialize init, DeltaUpdate update);

		private:
		static void init_win32();
	};
}

#include "Launcher.hpp" // Template implementation

#endif // LAUNCHER_H

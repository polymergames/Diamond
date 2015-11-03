/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LAUNCHER_H
#define D_LAUNCHER_H

#include "D_Config.h"
#include "D_Game.h"

namespace Diamond {
	class Launcher {
		public:
		static bool is_open;
		
		static struct Config config;

		/**
		 Call only once, at beginning of game!
		*/
		static void launch(Game &game);

		private:
		static void init_win32();
	};
}

#endif // D_LAUNCHER_H

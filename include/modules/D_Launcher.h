/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_LAUNCHER_H
#define D_LAUNCHER_H

#include "D_Config.h"
#include "D_Game.h"

namespace Diamond {
	namespace Launcher {
		extern bool is_open;
		
		extern Config config;

		/**
		 Call only once, at beginning of game!
		*/
		void launch(Game &game);

		void init_win32();
	};
}

#endif // D_LAUNCHER_H

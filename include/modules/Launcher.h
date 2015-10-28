/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>
#include "Config.h"
#include "Game.h"
#include "Graphics2D.h"
#include "Log.h"

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

#endif // LAUNCHER_H

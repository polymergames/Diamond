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

		/*
		 Call only once, at beginning of game!
		*/
		static void launch(Config &config);

		virtual ~Launcher();

		private:
		static std::unique_ptr<Launcher> launcher;
	};
}

#endif // LAUNCHER_H

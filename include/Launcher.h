/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>

namespace Diamond {
	struct Config {
		std::string game_name;
		int window_width;
		int window_height;
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

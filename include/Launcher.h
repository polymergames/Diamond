/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>
#include <memory>

namespace Diamond {
	class Launcher {
		public:
		static void launch(Config &config);
		virtual ~Launcher();

		private:
		static std::unique_ptr<Launcher> launcher;
	};

	struct Config {
		std::string game_name;
		int window_width;
		int window_height;
	};
}

#endif // LAUNCHER_H

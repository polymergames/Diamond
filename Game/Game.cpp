/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
using namespace Diamond;

class Init {
	public:
	void operator() () {
		std::cout << "Initializing..." << std::endl;
	}
};

class Update {
	public:
	void operator() (float delta) {
		std::cout << "Launcher::is_open is " << Launcher::is_open << std::endl;
		std::cin >> Launcher::is_open;
	}
};

int main(int argc, char *argv[]) {
	Config config = Config();
	Launcher::launch(config, Init(), Update());
	return 0;
}

/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
#include "Input.h"
using namespace Diamond;

float d = 0.0f;

class Init {
	public:
	void operator() () {
		std::cout << "Initializing..." << std::endl;
	}
};

class Update {
	public:
	void operator() (float delta) {
		//std::cout << "Delta is " << (d+=delta) << std::endl;
	}
};

int main(int argc, char *argv[]) {
	Config config = Config();
	Launcher::launch(config, Init(), Update());
	return 0;
}

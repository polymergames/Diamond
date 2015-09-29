/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"
using namespace Diamond;

int main(int argc, char *argv[]) {
	Config config = { "Game", 1280, 720 };
	Diamond::Launcher::launch(config);
	return 0;
}

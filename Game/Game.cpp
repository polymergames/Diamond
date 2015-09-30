/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"

int main(int argc, char *argv[]) {
	Diamond::Config config = { "Game", 1280, 720 };
	Diamond::Launcher::launch(config);
	return 0;
}

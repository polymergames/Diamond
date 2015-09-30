/*
 Copyright (c) 2015 Polymer Games
*/

#include "Launcher.h"

int main(int argc, char *argv[]) {
	Diamond::Config config = Diamond::Config();
	config.software_render = true;
	Diamond::Launcher::launch(config);
	return 0;
}

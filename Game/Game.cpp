/*
 Copyright (c) 2015 Polymer Games
 */

#include "Launcher.h"

int main(int argc, char *argv[]) {
	Launcher::launch();

	Launcher::cleanup();
	return 0;
}

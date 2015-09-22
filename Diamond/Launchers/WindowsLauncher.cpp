/*
 Copyright (c) 2015 Polymer Games
*/

#include "WindowsLauncher.h"

WindowsLauncher::WindowsLauncher() {
	Graphics::setGraphics(std::move(std::unique_ptr<SDLGraphics>(new SDLGraphics)));
}

WindowsLauncher::~WindowsLauncher() {
	// cleanup code
}

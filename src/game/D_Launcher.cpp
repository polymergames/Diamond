/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_Launcher.h"

#include "D_DesktopLogger.h"
#include "D_SDLRenderer2D.h"

bool Diamond::Launcher::is_open = true;
struct Diamond::Config Diamond::Launcher::config = Diamond::Config();

void Diamond::Launcher::launch(Game &game) {
#if defined __ANDROID__
	// Android launcher
#elif defined IOS // TODO: What is the IOS platform macro? Or define one manually!
	// IOS launcher
#elif defined _WIN32 || defined __APPLE__
	init_win32(); // Windows launcher (also being used for osx because no osx-specific implementation atm)
#else
	// TODO: Log this using logger, and use a better RAII-compliant exit method! (ex. exceptions)
	std::cout << "Platform unsupported!" << std::endl;
	std::exit();
#endif

	// Init game
	game.init();

	// Update
	while (Diamond::Launcher::is_open) {
		game.update(1.0f); // TODO: Implement delta time
		Diamond::Graphics2D::render();
	}

	// End game
	game.quit();
}

void Diamond::Launcher::init_win32() {
	Diamond::Log::setLogger(new DesktopLogger());

	Diamond::Graphics2D::set_renderer(new SDLRenderer2D());
	if (!Graphics2D::init_renderer()) {
		// TODO: Handle render initialization failure
	}
}

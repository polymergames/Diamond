/*
 Copyright (c) 2015 Polymer Games
*/

template <class Initialize, class DeltaUpdate> void Diamond::Launcher::launch(Diamond::Config &config, Initialize init, DeltaUpdate update) {
#if defined __ANDROID__
	// Android launcher
#elif defined IOS // TODO: What is the IOS platform macro? Or define one manually!
	// IOS launcher
#elif defined _WIN32 || defined __APPLE__
	init_win32(config); // Windows launcher (also being used for osx because no osx-specific implementation atm)
#else
	// TODO: Log this using logger, and use a better RAII-compliant exit method! (ex. exceptions)
	std::cout << "Platform unsupported!" << std::endl;
	std::exit();
#endif

	// Init game
	init();

	// Update
	while (Diamond::Launcher::is_open) {
		update(1.0f); // TODO: Implement delta time
		Diamond::Graphics2D::render();
	}
}

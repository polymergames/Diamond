/*
 Copyright (c) 2015 Polymer Games
*/

template <class Initialize, class DeltaUpdate> void Diamond::Launcher::launch(Diamond::Config &config, Initialize init, DeltaUpdate update) {
#if defined ANDROID
	// Android launcher
#elif defined IOS
	// IOS launcher
#elif defined OSX
	// OSX launcher
#else
	init_win32(config); // Windows launcher
#endif

	// Init game
	init();

	// Update
	while (Diamond::Launcher::is_open) {
		update(1.0f); // TODO: Implement delta time
		Diamond::Graphics2D::render();
	}
}

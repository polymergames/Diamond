/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLDiskJockey2D.h"

#include "SDL_mixer.h"

#include "D_Launcher.h"
#include "D_SDLSound2D.h"

bool Diamond::SDLDiskJockey2D::init() {
	if (Mix_OpenAudio(Launcher::config.audio_out_freq,
			MIX_DEFAULT_FORMAT,
			Launcher::config.audio_channels,
			Launcher::config.audio_out_sample_size) < 0) {
		std::cout << "SDL_mixer failed to initialize! SDL_mixer Error:" << Mix_GetError();
		return false;
	}
	return true;
}

Diamond::Sound2D *Diamond::SDLDiskJockey2D::load_sound(std::string path) {
	Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
	if (sound == NULL) {
		std::cout << "Failed to load sound " << path << "! SDL_mixer Error: " << Mix_GetError();
		return nullptr;
	}
	return new SDLSound2D(sound);
}

Diamond::SDLDiskJockey2D::~SDLDiskJockey2D() {
	Mix_Quit();
}

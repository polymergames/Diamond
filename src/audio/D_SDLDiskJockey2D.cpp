/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_SDLDiskJockey2D.h"

#include "SDL_mixer.h"

#include "D_Launcher.h"
#include "D_SDLMusic.h"
#include "D_SDLSound2D.h"

bool Diamond::SDLDiskJockey2D::init() {
	if (Mix_OpenAudio(Launcher::config.audio_out_freq,
			MIX_DEFAULT_FORMAT,
			Launcher::config.audio_channels,
			Launcher::config.audio_out_sample_size) < 0) {
		// TODO: Log error
		std::cout << "SDL_mixer failed to initialize! SDL_mixer Error:" << Mix_GetError();
		return false;
	}
	return true;
}

Diamond::Sound2D *Diamond::SDLDiskJockey2D::loadSound(std::string path) {
	Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
	if (sound == NULL) {
		// TODO: Log error
		std::cout << "Failed to load sound " << path << "! SDL_mixer Error: " << Mix_GetError();
		return nullptr;
	}
	return new SDLSound2D(sound);
}

Diamond::Music *Diamond::SDLDiskJockey2D::loadMusic(std::string path) {
	Mix_Music *music = Mix_LoadMUS(path.c_str());
	if (music == NULL) {
		// TODO: Log error
		std::cout << "Failed to load music " << path << "! SDL_mixer Error: " << Mix_GetError();
		return nullptr;
	}
	return new SDLMusic(music);
}

int Diamond::SDLDiskJockey2D::getMaxVolume() const {
	return MIX_MAX_VOLUME;
}

void Diamond::SDLDiskJockey2D::pauseMusic() {
	Mix_PauseMusic();
}

void Diamond::SDLDiskJockey2D::resumeMusic() {
	Mix_ResumeMusic();
}

void Diamond::SDLDiskJockey2D::stopMusic() {
	Mix_HaltMusic();
}

bool Diamond::SDLDiskJockey2D::isMusicPlaying() const {
	return Mix_PlayingMusic() ? !Mix_PausedMusic() : false;
}

int Diamond::SDLDiskJockey2D::getMusicVolume() const {
	return Mix_VolumeMusic(-1);
}

void Diamond::SDLDiskJockey2D::setMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

Diamond::SDLDiskJockey2D::~SDLDiskJockey2D() {
	Mix_Quit();
}

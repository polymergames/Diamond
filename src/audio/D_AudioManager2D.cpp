/*
 Copyright (c) 2015 Polymer Games
*/

#include "D_AudioManager2D.h"

#include <memory>

#include "D_DiskJockey2D.h"

namespace Diamond {
	namespace AudioManager2D {
		static std::unique_ptr<Diamond::DiskJockey2D> dj = nullptr;
	}
}

Diamond::Sound2D *Diamond::AudioManager2D::loadSound(std::string path) {
	return dj->loadSound(path);
}

Diamond::Music *Diamond::AudioManager2D::loadMusic(std::string path) {
	return dj->loadMusic(path);
}

int Diamond::AudioManager2D::getMaxVolume() {
	return dj->getMaxVolume();
}

void Diamond::AudioManager2D::pauseMusic() {
	dj->pauseMusic();
}

void Diamond::AudioManager2D::resumeMusic() {
	dj->resumeMusic();
}

void Diamond::AudioManager2D::stopMusic() {
	dj->stopMusic();
}

bool Diamond::AudioManager2D::isMusicPlaying() {
	return dj->isMusicPlaying();
}

int Diamond::AudioManager2D::getMusicVolume() {
	return dj->getMusicVolume();
}

void Diamond::AudioManager2D::setMusicVolume(int volume) {
	dj->setMusicVolume(volume);
}

bool Diamond::AudioManager2D::initDj(DiskJockey2D *dj) {
	if (AudioManager2D::dj == nullptr && dj != nullptr) {
		AudioManager2D::dj = std::unique_ptr<DiskJockey2D>(dj);
		return dj->init();
	}
	return false;
}

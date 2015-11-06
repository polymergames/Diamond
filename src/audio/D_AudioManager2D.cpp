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

Diamond::Sound2D *Diamond::AudioManager2D::load_sound(std::string path) {
	return dj->load_sound(path);
}

Diamond::Music *Diamond::AudioManager2D::load_music(std::string path) {
	return dj->load_music(path);
}

int Diamond::AudioManager2D::get_max_volume() {
	return dj->get_max_volume();
}

void Diamond::AudioManager2D::pause_music() {
	dj->pause_music();
}

void Diamond::AudioManager2D::resume_music() {
	dj->resume_music();
}

void Diamond::AudioManager2D::stop_music() {
	dj->stop_music();
}

bool Diamond::AudioManager2D::is_music_playing() {
	return dj->is_music_playing();
}

int Diamond::AudioManager2D::get_music_volume() {
	return dj->get_music_volume();
}

void Diamond::AudioManager2D::set_music_volume(int volume) {
	dj->set_music_volume(volume);
}

void Diamond::AudioManager2D::set_dj(Diamond::DiskJockey2D *dj) {
	AudioManager2D::dj = std::unique_ptr<DiskJockey2D>(dj);
}

bool Diamond::AudioManager2D::init_dj() {
	if (dj != nullptr)
		return dj->init();
	return false;
}

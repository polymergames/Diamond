/*
 Copyright (c) 2015 Polymer Games
*/

#include "AudioManager2D.h"

#include <memory>

namespace Diamond {
	static std::unique_ptr<Diamond::DiskJockey2D> dj = nullptr;
}

Diamond::Sound2D *Diamond::AudioManager2D::load_sound(std::string path) {
	return dj->load_sound(path);
}

void Diamond::AudioManager2D::set_dj(Diamond::DiskJockey2D *dj) {
	Diamond::dj = std::unique_ptr<DiskJockey2D>(dj);
}

bool Diamond::AudioManager2D::init_dj() {
	if (dj != nullptr)
		return dj->init();
	return false;
}

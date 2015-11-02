/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_DISK_JOCKEY_2D_H
#define SDL_DISK_JOCKEY_2D_H

#include "D_DiskJockey2D.h"

namespace Diamond {
	class SDLDiskJockey2D : public DiskJockey2D {
		public:
		bool init() override;

		Sound2D *load_sound(std::string path) override;

		~SDLDiskJockey2D();
	};
}

#endif // SDL_DISK_JOCKEY_2D_H

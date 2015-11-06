/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_DISK_JOCKEY_2D_H
#define D_SDL_DISK_JOCKEY_2D_H

#include "D_DiskJockey2D.h"

namespace Diamond {
	class SDLDiskJockey2D : public DiskJockey2D {
		public:
		bool init() override;

		Sound2D *loadSound(std::string path) override;

		Music *loadMusic(std::string path) override;

		int getMaxVolume() const override;

		void pauseMusic() override;

		void resumeMusic() override;

		void stopMusic() override;

		bool isMusicPlaying() const override;

		int getMusicVolume() const override;

		void setMusicVolume(int volume) override;

		~SDLDiskJockey2D();
	};
}

#endif // D_SDL_DISK_JOCKEY_2D_H

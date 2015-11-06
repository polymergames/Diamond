/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_DISK_JOCKEY_2D_H
#define D_DISK_JOCKEY_2D_H

#include <iostream>

#include "D_Sound2D.h"
#include "D_Music.h"

namespace Diamond {
	class DiskJockey2D {
		public:
		virtual bool init() = 0;

		virtual Sound2D *loadSound(std::string path) = 0;

		virtual Music *loadMusic(std::string path) = 0;

		virtual int getMaxVolume() const = 0;

		virtual void pauseMusic() = 0;

		virtual void resumeMusic() = 0;

		virtual void stopMusic() = 0;

		virtual bool isMusicPlaying() const = 0;

		virtual int getMusicVolume() const = 0;

		virtual void setMusicVolume(int volume) = 0;

		virtual ~DiskJockey2D() {};
	};
}

#endif // D_DISK_JOCKEY_2D_H

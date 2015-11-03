/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_DISK_JOCKEY_2D_H
#define D_DISK_JOCKEY_2D_H

#include <iostream>

#include "D_Music.h"
#include "D_Sound2D.h"

namespace Diamond {
	class DiskJockey2D {
		public:
		virtual bool init() = 0;

		virtual Sound2D *load_sound(std::string path) = 0;

		virtual Music *load_music(std::string path) = 0;

		virtual int get_max_volume() = 0;

		virtual void pause_music() = 0;

		virtual void resume_music() = 0;

		virtual void stop_music() = 0;

		virtual bool is_music_playing() = 0;

		virtual int get_music_volume() = 0;

		virtual void set_music_volume(int volume) = 0;

		virtual ~DiskJockey2D() {};
	};
}

#endif // D_DISK_JOCKEY_2D_H

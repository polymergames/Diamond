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

		Sound2D *load_sound(std::string path) override;

		Music *load_music(std::string path) override;

		int get_max_volume() const override;

		void pause_music() override;

		void resume_music() override;

		void stop_music() override;

		bool is_music_playing() const override;

		int get_music_volume() const override;

		void set_music_volume(int volume) override;

		~SDLDiskJockey2D();
	};
}

#endif // D_SDL_DISK_JOCKEY_2D_H

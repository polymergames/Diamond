/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_MUSIC_H
#define D_SDL_MUSIC_H

#include "SDL_Mixer.h"

#include "D_Music.h"

namespace Diamond {
	/**
	 Note: the pause(), resume(), stop(), and set_volume() functions affect whatever music is active,
	 even if it is not this one.
	*/
	class SDLMusic : public Music {
		public:
		SDLMusic(Mix_Music *music);

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		void set_loop(bool loop) override;

		int get_volume() override;

		void set_volume(int volume) override;

		~SDLMusic();

		private:
		Mix_Music *music;
		int loop; ///< -1 means that the music will loop; otherwise, should be 1.
	};
}

#endif // D_SDL_MUSIC_H

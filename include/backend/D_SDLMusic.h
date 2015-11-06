/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_MUSIC_H
#define D_SDL_MUSIC_H

#include "SDL_Mixer.h"

#include "D_Music.h"

namespace Diamond {
	/**
	 Note: the pause(), resume(), stop(), and setVolume() functions affect whatever music is active,
	 even if it is not this one.
	*/
	class SDLMusic : public Music {
		public:
		SDLMusic(Mix_Music *music);

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		void setLoop(bool loop) override;

		int getVolume() const override;

		void setVolume(int volume) override;

		~SDLMusic();

		private:
		Mix_Music *music;
		int loop; ///< -1 means that the music will loop; otherwise, should be 1.
	};
}

#endif // D_SDL_MUSIC_H

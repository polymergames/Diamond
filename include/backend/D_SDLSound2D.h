/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_SOUND_2D_H
#define D_SDL_SOUND_2D_H

#include "SDL_mixer.h"

#include "D_Sound2D.h"

namespace Diamond {
	/**
	 Note: the pause(), resume(), and stop() functions are not very reliable in this implementation.
	 They act on the last channel that this sound played on, even if this sound is no longer on that channel
	 (ie if you call these functions, you might be affecting a completely different sound).
	*/
	class SDLSound2D : public Sound2D {
		public:
		SDLSound2D(Mix_Chunk *sound);

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		int get_volume() const override;

		void set_volume(int volume) override;
		
		~SDLSound2D();

		private:
		Mix_Chunk *sound;
		int channel;
	};
}

#endif // D_SDL_SOUND_2D_H

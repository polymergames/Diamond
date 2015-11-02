/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_SOUND_2D_H
#define D_SDL_SOUND_2D_H

#include "SDL_mixer.h"

#include "D_Sound2D.h"

namespace Diamond {
	class SDLSound2D : public Sound2D {
		public:
		SDLSound2D(Mix_Chunk *sound);

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		int get_volume() override;

		void set_volume(int volume) override;
		
		~SDLSound2D();

		private:
		Mix_Chunk *sound;
		int channel;
	};
}

#endif // D_SDL_SOUND_2D_H

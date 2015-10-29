/*
 Copyright (c) 2015 Polymer Games
 */

#ifndef D_SDL_SOUND_H
#define D_SDL_SOUND_H

#include "Sound.h"
#include "SDL_mixer.h"

namespace Diamond {
	class SDLSound : public Sound {
		public:
		SDLSound(Mix_Chunk *sound);
		void play();
		
		private:
		Mix_Chunk *sound;
	};
}

#endif // D_SDL_SOUND_H
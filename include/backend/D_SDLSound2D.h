/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
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

		~SDLSound2D();

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		int getVolume() const override;

		void setVolume(int volume) override;

	private:
		Mix_Chunk *sound;
		int channel;
	};
}

#endif // D_SDL_SOUND_2D_H

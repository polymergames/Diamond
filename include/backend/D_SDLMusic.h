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

		~SDLMusic();

		void play() override;

		void pause() override;

		void resume() override;

		void stop() override;

		void setLoop(bool loop) override;

		int getVolume() const override;

		void setVolume(int volume) override;

	private:
		Mix_Music *music;
		int loop; ///< -1 means that the music will loop; otherwise, should be 1.
	};
}

#endif // D_SDL_MUSIC_H

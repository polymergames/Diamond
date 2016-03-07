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

#ifndef D_MUSIC_H
#define D_MUSIC_H

namespace Diamond {
	/**
	 An audio object meant to be played as background music. 
	 In some implementations (ie. SDL), only one Music object can be playing at a time.
	 Also, some of these functions may affect whichever track is currently playing, even if it is not this one
	 (this happens in the SDL mixer implementation with pause(), resume(), stop(), and set_volume()).
	 To manipulate all/main music that is active, use the functions in AudioManager2D.
	*/
	class Music {
	public:
		virtual ~Music() {};

		virtual void play() = 0;

		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void stop() = 0;

		/**
		 Sets whether or not this music should loop.
		 In some implementations (ie. SDL), this will only take effect the next time play() is called for this music.
		*/
		virtual void setLoop(bool loop) = 0;

		virtual int getVolume() const = 0;

		/**
		 Note: you can use the getMaxVolume() function in AudioManager2D to scale your volume values.
		*/
		virtual void setVolume(int volume) = 0;
	};
}

#endif // D_MUSIC_H

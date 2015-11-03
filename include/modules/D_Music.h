/*
 Copyright (c) 2015 Polymer Games
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

		virtual void play() = 0;

		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void stop() = 0;

		/**
		 Sets whether or not this music should loop.
		 In some implementations (ie. SDL), this will only take effect the next time play() is called for this music.
		*/
		virtual void set_loop(bool loop) = 0;

		virtual int get_volume() = 0;

		/**
		 Note: you can use the get_max_volume() function in AudioManager2D to scale your volume values.
		*/
		virtual void set_volume(int volume) = 0;

		virtual ~Music() {};

	};
}

#endif // D_MUSIC_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SOUND_2D_H
#define D_SOUND_2D_H

namespace Diamond {
	/**
	 If using the SDL sound implementation, see D_SDLSound2D.h for an important note on the reliability of some functions.
	*/
	class Sound2D {
		public:
		// TODO: bool is_playing()
		
		virtual void play() = 0;
		
		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void stop() = 0;

		virtual int getVolume() const = 0;
		
		/**
		 Note: you can use the getMaxVolume() function in AudioManager2D to scale your volume values.
		*/
		virtual void setVolume(int volume) = 0;

		virtual ~Sound2D() {};
	};
}

#endif // D_SOUND_2D_H

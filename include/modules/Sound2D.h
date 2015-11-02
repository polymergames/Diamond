/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SOUND_2D_H
#define D_SOUND_2D_H

namespace Diamond {
	class Sound2D {
		public:
		// TODO: bool is_playing()
		
		virtual void play() = 0;
		
		virtual void pause() = 0;

		virtual void resume() = 0;

		virtual void stop() = 0;

		virtual int get_volume() = 0;

		virtual void set_volume(int volume) = 0;

		virtual ~Sound2D() {};
	};
}

#endif // D_SOUND_2D_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SOUND_2D_H
#define D_SOUND_2D_H

namespace Diamond {
	class Sound2D {
		public:
		virtual void play() = 0;
		virtual ~Sound2D() {};
	};
}

#endif // D_SOUND_2D_H

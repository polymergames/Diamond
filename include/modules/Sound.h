/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SOUND_H
#define D_SOUND_H

namespace Diamond {
	class Sound {
		public:
		virtual void play() = 0;
		virtual ~Sound() {};
	};
}

#endif // D_SOUND_H
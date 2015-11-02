/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_DISK_JOCKEY_2D_H
#define D_DISK_JOCKEY_2D_H

#include <iostream>
#include "Sound2D.h"

namespace Diamond {
	class DiskJockey2D {
		public:
		virtual bool init() = 0;
		virtual Sound2D *load_sound(std::string path) = 0;
		virtual ~DiskJockey2D() {};
	};
}

#endif // D_DISK_JOCKEY_2D_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Config.h"

namespace Diamond {
	class Texture {
		public:
		Texture(int width, int height);
		
		virtual RGBA get_color();

		virtual void set_color(RGBA color);
		
		virtual ~Texture();

		int width, height;
		
		protected:
		RGBA color;
	};
}

#endif // TEXTURE_H

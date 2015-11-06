/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_TEXTURE_H
#define D_TEXTURE_H

#include "D_Config.h"

namespace Diamond {
	class Texture {
		public:
		Texture(int width, int height);
		
		virtual RGBA getColor() const;

		virtual void setColor(RGBA color);
		
		virtual ~Texture();

		int width, height;
		
		protected:
		RGBA color;
	};
}

#endif // D_TEXTURE_H

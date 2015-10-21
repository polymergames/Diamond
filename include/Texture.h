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
        
		virtual void set_color(RGB color) = 0;

        int get_width();
        int get_height();
        
		virtual ~Texture();
        
        private:
        int width, height;
	};
}

#endif // TEXTURE_H

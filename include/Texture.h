/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef TEXTURE_H
#define TEXTURE_H

namespace Diamond {
	class Texture {
		public:
        Texture(int width, int height);
        
        int get_width();
        int get_height();
        
		virtual ~Texture();
        
        private:
        int width, height;
	};
}

#endif // TEXTURE_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_GRAPHICS_2D_H
#define D_GRAPHICS_2D_H

#include <iostream>

#include "D_GameObject2D.h"
#include "D_Texture.h"

namespace Diamond {
	class Renderer2D;
	
	namespace Graphics2D {
		
		/**
		 Loads an image file as a texture.
		 Returns nullptr if texture failed to load.
		*/
		Texture *loadTexture(std::string path);
		
		// TODO: move functions like loadTexture to a public resource management header, and move these to a backend header (ie not visible to users)
		bool initRenderer(Renderer2D *renderer); // returns whether initialization was successful
		void render(); // renders everything
		void genRenderObj(GameObject2D *parent, Texture *texture);
		void activateRenderObj(unsigned long index);
		void deactivateRenderObj(unsigned long index);
		void destroyRenderObj(unsigned long index);
		void destroyInactiveRenderObj(unsigned long index);
	};
}

#endif // D_GRAPHICS_2D_H

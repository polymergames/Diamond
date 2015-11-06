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
		Texture *load_texture(std::string path);
		
		// TODO: move functions like load_texture to a public resource management header, and move these to a backend header (ie not visible to users)
		bool init_renderer(Renderer2D *renderer); // returns whether initialization was successful
		void render();
		void gen_render_obj(GameObject2D *parent, Texture *texture);
		void activate_render_obj(unsigned long index);
		void deactivate_render_obj(unsigned long index);
		void destroy_render_obj(unsigned long index);
		void destroy_inactive_render_obj(unsigned long index);
	};
}

#endif // D_GRAPHICS_2D_H

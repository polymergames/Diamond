/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_GRAPHICS_2D_H
#define D_GRAPHICS_2D_H

#include <memory>

#include "D_Renderer2D.h"

namespace Diamond {
	namespace Graphics2D {
		/**
		 Loads an image file as a texture.
		 Returns nullptr if texture failed to load.
		*/
		Texture *load_texture(std::string path);
		
		// Don't call unless you know what you're doing!
		void set_renderer(Renderer2D *renderer);
		bool init_renderer(); // returns whether initialization was successful
		void render();
		void gen_render_obj(GameObject2D *parent, Texture *texture);
		void activate_render_obj(unsigned long index);
		void deactivate_render_obj(unsigned long index);
		void destroy_render_obj(unsigned long index);
		void destroy_inactive_render_obj(unsigned long index);
	};
}

#endif // D_GRAPHICS_2D_H

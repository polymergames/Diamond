/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GRAPHICS_2D_H
#define GRAPHICS_2D_H

#include <iostream>
#include <memory>
#include "Config.h"
#include "Renderer2D.h"

namespace Diamond {
	class Graphics2D {
		public:
		
		static Texture *load_texture(std::string path);
		
		// Don't call unless you know what you're doing!
		static void setRenderer(Renderer2D *renderer);
		static bool init_renderer();
		static void render();
		static void gen_render_obj(GameObject2D *parent, Texture *texture);
		static void activate_render_obj(unsigned long index);
		static void deactivate_render_obj(unsigned long index);
		static void destroy_render_obj(unsigned long index);

		private:
		static std::unique_ptr<Renderer2D> renderer;
	};
}

#endif // GRAPHICS_2D_H

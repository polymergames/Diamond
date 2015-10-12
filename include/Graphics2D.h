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
		/**
		 Don't call unless you know what you're doing!
		*/
		static void setRenderer(Renderer2D *renderer);
		static bool init_renderer(Config &config);
		static void render();
		static void gen_render_obj(GameObject2D *parent, Texture *texture);
		static void destroy_render_obj(unsigned long index);

		private:
		static std::unique_ptr<Renderer2D> renderer;
	};
}

#endif // GRAPHICS_2D_H

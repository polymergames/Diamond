/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <memory>
#include "Config.h"
#include "Renderer.h"

namespace Diamond {
	class Graphics {
		public:
		/**
		 Don't call unless you know what you're doing!
		*/
		static void setRenderer(Renderer *renderer);
		static bool init_renderer(Config &config);
		static void render();

		private:
		static std::unique_ptr<Renderer> renderer;
	};
}

#endif // GRAPHICS_H

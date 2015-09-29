/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <memory>
#include "Renderer.h"

namespace Diamond {
	class Graphics {
		public:
		static void setRenderer(Renderer *renderer);

		private:
		static std::unique_ptr<Renderer> renderer;
	};
}

#endif // GRAPHICS_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <memory>
#include "Renderer.h"
#include "SoftSprite.h"

namespace Diamond {
	class Graphics {
		public:
		static SoftSprite *gen_soft_sprite(std::string img);

		/*
		 Don't call unless you know what you're doing!
		*/
		static void setRenderer(Renderer *renderer);

		private:
		static std::unique_ptr<Renderer> renderer;
	};
}

#endif // GRAPHICS_H

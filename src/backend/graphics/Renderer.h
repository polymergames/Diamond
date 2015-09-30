/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "SoftSprite.h"

namespace Diamond {
	class Renderer {
		public:
		virtual SoftSprite *gen_soft_sprite(std::string img) = 0;
		virtual int blit_soft_sprite(SoftSprite &src) = 0;
		virtual int blit_soft_sprite(SoftSprite &src, SoftSprite &dest) = 0;

		virtual ~Renderer();
	};
}

#endif // RENDERER_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_RENDERER_2D_H
#define D_RENDERER_2D_H

#include <iostream>

#include "D_GameObject2D.h"
#include "D_Texture.h"

namespace Diamond {
	class Renderer2D {
		public:
		virtual bool init() = 0;
		virtual void render() = 0;
		virtual Texture *loadTexture(std::string path) = 0;
		virtual void genRenderObj(GameObject2D *parent, Texture *texture) = 0;
		virtual void activateRenderObj(unsigned long index) = 0;
		virtual void deactivateRenderObj(unsigned long index) = 0;
		virtual void destroyRenderObj(unsigned long index) = 0;
		virtual void destroyInactiveRenderObj(unsigned long index) = 0;
		virtual ~Renderer2D() {};
	};
}

#endif // D_RENDERER_2D_H

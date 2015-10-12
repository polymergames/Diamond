/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef SDL_RENDER_OBJ_2D_H
#define SDL_RENDER_OBJ_2D_H

#include "RenderObj2D.h"

namespace Diamond {
	class SDLRenderObj2D : public RenderObj2D {
		public:
		SDL_Texture *texture;

		SDLRenderObj2D(GameObject2D *parent, Texture *texture, Transform2 &transform);

		void set_texture(Texture *texture);

		void arm_parent();
	};
}

#endif // SDL_RENDER_OBJ_2D_H

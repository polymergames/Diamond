/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_RENDER_OBJ_2D_H
#define D_SDL_RENDER_OBJ_2D_H

#include "RenderObj2D.h"
#include "SDL.h"
#include "SDLTexture.h"

namespace Diamond {
	class SDLRenderObj2D : public RenderObj2D {
		public:
		SDLTexture *texture;
		SDL_RendererFlip flip;

		SDLRenderObj2D(GameObject2D *parent, Texture *texture);

		void set_texture(Texture *texture);

		void flip_x();
		void flip_y();

		bool is_flipped_x();
		bool is_flipped_y();

		void render(SDL_Renderer *renderer);
		
		void arm_parent();
	};
}

#endif // D_SDL_RENDER_OBJ_2D_H

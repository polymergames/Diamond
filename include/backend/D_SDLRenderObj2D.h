/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_RENDER_OBJ_2D_H
#define D_SDL_RENDER_OBJ_2D_H

#include "SDL.h"

#include "D_RenderObj2D.h"
#include "D_SDLTexture.h"

namespace Diamond {
	class SDLRenderObj2D : public RenderObj2D {
		public:
		SDLTexture *texture;
		SDL_RendererFlip flip;

		SDLRenderObj2D(GameObject2D *parent, Texture *texture);

		void set_texture(Texture *texture) override;

		void flip_x() override;
		void flip_y() override;

		int is_flipped_x() override;
		int is_flipped_y() override;

		void render(SDL_Renderer *renderer);
		
		void arm_parent();
	};
}

#endif // D_SDL_RENDER_OBJ_2D_H

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

		SDLRenderObj2D(GameObject2D *parent, Texture *texture);

		void set_texture(Texture *texture) override;

		void flip_x() override;
		void flip_y() override;

		int is_flipped_x() const override;
		int is_flipped_y() const override;

		void render(SDL_Renderer *renderer);
		
		void arm_parent();

		private:
		SDLTexture *texture;
		SDL_RendererFlip flip;
	};
}

#endif // D_SDL_RENDER_OBJ_2D_H

/*
 Copyright (c) 2015 Polymer Games
*/

#ifndef D_SDL_RENDER_OBJ_2D_H
#define D_SDL_RENDER_OBJ_2D_H

#include "SDL.h"

#include "D_RenderObj2D.h"

namespace Diamond {
	class SDLTexture;
	class SDLRenderObj2D : public RenderObj2D {
		public:

		SDLRenderObj2D(GameObject2D *parent, Texture *texture);

		void setTexture(Texture *texture) override;

		void flipX() override;
		void flipY() override;

		int isFlippedX() const override;
		int isFlippedY() const override;

		void render(SDL_Renderer *renderer);
		
		void armParent();

		private:
		SDLTexture *texture;
		SDL_RendererFlip flip;
	};
}

#endif // D_SDL_RENDER_OBJ_2D_H

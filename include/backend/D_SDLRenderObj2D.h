/*
    Copyright 2015 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
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

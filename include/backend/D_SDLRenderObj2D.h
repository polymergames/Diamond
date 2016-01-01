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
		SDLTexture *texture;
		SDL_RendererFlip flip;
		Vector2<int> size;

		SDLRenderObj2D(renderobj_id obj_id, Texture *texture, transform2_id transform, float scale);

		void setTexture(Texture *texture, float scale) override;
		void applyScale(float scale) override;

		void flipX() override;
		void flipY() override;

		int isFlippedX() const override;
		int isFlippedY() const override;
	};
}

#endif // D_SDL_RENDER_OBJ_2D_H

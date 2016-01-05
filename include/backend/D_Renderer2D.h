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

#ifndef D_RENDERER_2D_H
#define D_RENDERER_2D_H

#include <iostream>

#include "Q_typedefs.h"

#include "D_RenderObj2D.h"
#include "D_Texture.h"
#include "D_typedefs.h"

namespace Diamond {
	class Renderer2D {
	public:
		virtual ~Renderer2D() {}

		virtual bool init() = 0;
		
		virtual void renderAll() = 0;
		
		virtual Vector2<int> getResolution() = 0;

		virtual Diamond::Vector2<int> getScreenResolution() = 0;

		virtual Texture *loadTexture(std::string path) = 0;
		
		virtual RenderObj2D *getRenderObj(renderobj_id render_obj) = 0;
		virtual renderobj_id genRenderObj(Texture *texture, transform2_id transform, float scale) = 0;
		virtual void freeRenderObj(renderobj_id render_obj) = 0;
	};
}

#endif // D_RENDERER_2D_H

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

#ifndef D_GRAPHICS_2D_H
#define D_GRAPHICS_2D_H

#include <iostream>
#include "Q_typedefs.h"

#include "D_RenderObj2D.h"
#include "D_Texture.h"
#include "D_typedefs.h"

namespace Diamond {
	class Renderer2D;
	
	namespace Graphics2D {
		
		/**
		 Loads an image file as a texture.
		 Returns nullptr if texture failed to load.
		*/
		Texture *loadTexture(std::string path);
		
		// TODO: move functions like loadTexture to a public resource management header, and move these to a backend header (ie not visible to users)
		bool initRenderer(Renderer2D *renderer); // returns whether initialization was successful
		void renderAll(); // renders everything
		RenderObj2D *getRenderObj(renderobj_id render_obj); // returned pointer is only temporarily valid
		renderobj_id genRenderObj(Texture *texture, transform2_id transform);
		void freeRenderObj(renderobj_id render_obj);
	};
}

#endif // D_GRAPHICS_2D_H

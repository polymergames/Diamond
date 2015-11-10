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

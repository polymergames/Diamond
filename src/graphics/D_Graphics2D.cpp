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

#include "D_Graphics2D.h"

#include <memory>

#include "D_Renderer2D.h"

namespace Diamond {
	namespace Graphics2D {
		static std::unique_ptr<Diamond::Renderer2D> renderer = nullptr;
	}
}

Diamond::Texture *Diamond::Graphics2D::loadTexture(std::string path) {
	return renderer->loadTexture(path);
}

bool Diamond::Graphics2D::initRenderer(Renderer2D *renderer) {
	Graphics2D::renderer = std::unique_ptr<Renderer2D>(renderer);
	return renderer->init();
}

void Diamond::Graphics2D::renderAll() {
	renderer->renderAll();
}

Diamond::RenderObj2D *Diamond::Graphics2D::getRenderObj(renderobj_id render_obj) {
	return renderer->getRenderObj(render_obj);
}

renderobj_id Diamond::Graphics2D::genRenderObj(Texture *texture, transform2_id transform, float scale) {
	return renderer->genRenderObj(texture, transform, scale);
}

void Diamond::Graphics2D::freeRenderObj(renderobj_id render_obj) {
	renderer->freeRenderObj(render_obj);
}

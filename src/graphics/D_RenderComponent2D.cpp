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

#include "D_RenderComponent2D.h"

#include "D_Launcher.h"

Diamond::RenderComponent2D::RenderComponent2D(Texture *sprite, bool visible, float scale)
	: RenderComponent2D(std::shared_ptr<Texture>(sprite), visible, scale) {}

Diamond::RenderComponent2D::RenderComponent2D(std::shared_ptr<Texture> sprite, bool visible, float scale)
	: sprite(sprite), visible(visible), scale(scale) {}

void Diamond::RenderComponent2D::setParent(Entity2D *parent) {
	if (visible) {
		render_obj = Graphics2D::genRenderObj(sprite.get(), parent->getTransformID(), scale);
	}
	else {
		render_obj = Diamond::INVALID;
	}
}

Diamond::RenderComponent2D::~RenderComponent2D() {
	// TODO: find exception-safer method of memory management. ie it's possible that render_obj has been destroyed/game has ended/crashed even if is_open = true
	if (Launcher::is_open) {
		freeRenderObj();
	}
}

void Diamond::RenderComponent2D::freeRenderObj() {
	if ((tD_index)render_obj != Diamond::INVALID) {
		Graphics2D::freeRenderObj(render_obj);
		render_obj = Diamond::INVALID;
	}
}

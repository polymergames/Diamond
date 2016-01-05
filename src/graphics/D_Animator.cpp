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

#include "D_Animator2D.h"

#include "D_RenderComponent2D.h"

Diamond::Animator2D::Animator2D(Entity2D *parent, Animation2D *anim) : Behavior(parent), anim(anim), cur_frame(0), elapsed(0) {
	renderer = parent->getComponent<RenderComponent2D>();
	if (!renderer) {
		renderer = new RenderComponent2D(parent, anim->sprites[0]);
		parent->addComponent(renderer);
	}
}

void Diamond::Animator2D::update(tD_delta delta) {
	elapsed += delta;
	if (elapsed > anim->frame_length) {
		cur_frame = (cur_frame + elapsed / anim->frame_length) % anim->sprites.size();
		renderer->setSprite(anim->sprites[cur_frame]);
		elapsed %= anim->frame_length;
	}
}

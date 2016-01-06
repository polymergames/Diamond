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

#include "D_AnimatorSheet.h"

#include "D_RenderComponent2D.h"

Diamond::AnimatorSheet::AnimatorSheet(Entity2D *parent, AnimationSheet *anim) : Behavior(parent), anim(anim), cur_frame(0), elapsed(0) {
	if (!(anim->sprite_sheet) || anim->num_frames == 0) {
		// TODO: throw exception or log error
	}
	renderer = parent->getComponent<RenderComponent2D>();
	if (!renderer) {
		renderer = new RenderComponent2D(parent, anim->sprite_sheet);
		parent->addComponent(renderer);
	}
	else {
		renderer->setSprite(anim->sprite_sheet);
	}
	initClip();
}

void Diamond::AnimatorSheet::setAnimation(AnimationSheet *anim) {
	if (!(anim->sprite_sheet) || anim->num_frames == 0) {
		// TODO: throw exception or log error
	}
	this->anim = anim;
	renderer->setSprite(anim->sprite_sheet);
	cur_frame = 0;
	elapsed = 0;
	initClip();
}

void Diamond::AnimatorSheet::update(tD_delta delta) {
	elapsed += delta;
	if (elapsed > anim->frame_length) {
		cur_frame = (cur_frame + elapsed / anim->frame_length) % anim->num_frames;
		renderer->setClip((cur_frame % anim->columns) * frame_width, (cur_frame / anim->columns) * frame_height);
		elapsed %= anim->frame_length;
	}
}

void Diamond::AnimatorSheet::initClip() {
	frame_width = anim->sprite_sheet->width / anim->columns;
	frame_height = anim->sprite_sheet->height / anim->rows;
	renderer->initClip();
	renderer->setClip(0, 0, frame_width, frame_height);
}

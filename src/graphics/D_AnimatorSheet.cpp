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

Diamond::AnimatorSheet::AnimatorSheet(Entity2D *parent, Renderer2D *renderer, AnimationSheet *anim) : Behavior(parent), anim(anim), cur_frame(0), elapsed(0) {
    if (!(anim->sprite_sheet) || anim->num_frames == 0) {
        // TODO: throw exception or log error
        std::cout << "AnimatorSheet2D: The given animation for parent " << parent->getName() << " is empty!" << std::endl;
    }

    rendercomp = parent->getComponent<RenderComponent2D>();
    if (!rendercomp) {
        rendercomp = new RenderComponent2D(parent, renderer, anim->sprite_sheet);
        parent->addComponent(rendercomp);
    }

    rendercomp->setSprite(anim->sprite_sheet);
    initClip();
}

void Diamond::AnimatorSheet::setAnimation(AnimationSheet *anim) {
    if (!(anim->sprite_sheet) || anim->num_frames == 0) {
        // TODO: throw exception or log error
    }
    this->anim = anim;
    rendercomp->setSprite(anim->sprite_sheet);
    cur_frame = 0;
    elapsed = 0;
    initClip();
}

void Diamond::AnimatorSheet::update(tD_delta delta) {
    elapsed += delta;
    if (elapsed > anim->frame_length) {
        cur_frame = (cur_frame + elapsed / anim->frame_length) % anim->num_frames;
        rendercomp->setClip((cur_frame % anim->columns) * frame_width, (cur_frame / anim->columns) * frame_height);
        elapsed %= anim->frame_length;
    }
}

void Diamond::AnimatorSheet::initClip() {
    frame_width = anim->sprite_sheet->getWidth() / anim->columns;
    frame_height = anim->sprite_sheet->getHeight() / anim->rows;
    rendercomp->initClip();
    rendercomp->setClip(0, 0, frame_width, frame_height);
}

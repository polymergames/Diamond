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

Diamond::Animator2D::Animator2D(Entity2D *parent, Renderer2D *renderer, Animation2D *anim) : Behavior(parent), anim(anim), cur_frame(0), elapsed(0) {
    if (anim->sprites.size() == 0) {
        // TODO: throw exception or log error
        std::cout << "Animator2D: The given animation for parent " << parent->getName() << " is empty!" << std::endl;
    }

    rendercomp = parent->getComponent<RenderComponent2D>();
    if (!rendercomp) {
        rendercomp = new RenderComponent2D(parent, renderer, anim->sprites[0]);
        parent->addComponent(rendercomp);
    }
    else {
        rendercomp->setSprite(anim->sprites[0]);
    }
    
}

void Diamond::Animator2D::setAnimation(Animation2D *anim) {
    if (anim->sprites.size() == 0) {
        // TODO: throw exception or log error
    }
    this->anim = anim;
    rendercomp->setSprite(anim->sprites[0]);
    cur_frame = 0;
    elapsed = 0;
}

void Diamond::Animator2D::update(tD_delta delta) {
    elapsed += delta;
    if (elapsed > anim->frame_length) {
        cur_frame = (cur_frame + elapsed / anim->frame_length) % anim->sprites.size();
        rendercomp->setSprite(anim->sprites[cur_frame]);
        elapsed %= anim->frame_length;
    }
}

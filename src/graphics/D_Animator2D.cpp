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
#include "D_Log.h"

Diamond::Animator2D::Animator2D(RenderComponent2D *rendercomp, const Animation2D *anim) 
    : rendercomp(rendercomp), anim(anim), cur_frame(0), elapsed(0) {
    if (!rendercomp) {
        Log::log("Animator2D ERROR: The given render component is nulL!");
    }
    else if (!anim || anim->sprites.size() == 0) {
        // TODO: throw exception?
        Log::log("Animator2D ERROR: The given animation is empty!");
    }
    else {
        rendercomp->setSprite(anim->sprites[0]);
    }
}

void Diamond::Animator2D::setAnimation(const Animation2D *anim) {
    if (!anim || anim->sprites.size() == 0) {
        // TODO: throw exception?
        Log::log("Animator2D ERROR: Tried to set an empty animation!");
        return;
    }
    this->anim = anim;
    rendercomp->setSprite(anim->sprites[0]);
    cur_frame = 0;
    elapsed = 0;
}
/*
void Diamond::Animator2D::update(tD_delta delta) {
    elapsed += delta;
    if (elapsed > anim->frame_length) {
        cur_frame = (cur_frame + elapsed / anim->frame_length) % anim->sprites.size();
        rendercomp->setSprite(anim->sprites[cur_frame]);
        elapsed %= anim->frame_length;
    }
}*/

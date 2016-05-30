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

Diamond::Animator2D::Animator2D(Renderer2D *renderer, 
                                renderobj_id render_obj, 
                                const Animation2D *anim)
    : m_renderer(renderer), m_render_obj(render_obj), m_anim(anim), m_cur_frame(0), m_elapsed(0) {
    if (!renderer) {
        Log::log("Animator2D ERROR: The given renderer is null!");
    }
    setAnimation(anim);
}

Diamond::Animator2D::Animator2D(const SharedPtr<RenderComponent2D> &rcomp,
                                const Animation2D *anim)
    : Animator2D(rcomp->getRenderer(), rcomp->getRenderObj(), anim) {}


void Diamond::Animator2D::setAnimation(const Animation2D *anim) {
    if (!anim || anim->sprites.size() == 0) {
        // TODO: throw exception?
        Log::log("Animator2D ERROR: Tried to set an empty animation!");
        return;
    }
    m_anim      = anim;
    m_renderer->getRenderObj(m_render_obj)->setTexture(m_anim->sprites[0].get());
    m_cur_frame = 0;
    m_elapsed   = 0;
}

void Diamond::Animator2D::update(tD_delta delta) {
    m_elapsed += delta;
    if (m_elapsed > m_anim->frame_length) {
        m_cur_frame = (m_cur_frame + m_elapsed / m_anim->frame_length) % m_anim->sprites.size();
        m_renderer->getRenderObj(m_render_obj)->setTexture(m_anim->sprites[m_cur_frame].get());
        m_elapsed %= m_anim->frame_length;
    }
}

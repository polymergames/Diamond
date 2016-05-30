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
#include "D_Log.h"

Diamond::AnimatorSheet::AnimatorSheet(Renderer2D *renderer,
                                      renderobj_id render_obj,
                                      const AnimationSheet *anim)
    : m_renderer(renderer), m_render_obj(render_obj), m_anim(anim), m_cur_frame(0), m_elapsed(0) {
    if (!renderer) {
        Log::log("AnimatorSheet ERROR: The given renderer is nulL!");
    }
    setAnimation(anim);
}

Diamond::AnimatorSheet::AnimatorSheet(const SharedPtr<RenderComponent2D> &rcomp,
                                      const AnimationSheet *anim)
    : AnimatorSheet(rcomp->getRenderer(), rcomp->getRenderObj(), anim) {}


void Diamond::AnimatorSheet::setAnimation(const AnimationSheet *anim) {
    if (!anim || !(anim->sprite_sheet) || anim->num_frames == 0) {
        // TODO: throw exception?
        Log::log("AnimatorSheet ERROR: Tried to set an empty animation!");
        return;
    }

    m_anim      = anim;
    m_renderer->getRenderObj(m_render_obj)->setTexture(anim->sprite_sheet.get());
    m_cur_frame = 0;
    m_elapsed   = 0;

    initClip();
}


void Diamond::AnimatorSheet::update(tD_delta delta) {
    m_elapsed += delta;

    if (m_elapsed > m_anim->frame_length) {
        m_cur_frame = (m_cur_frame + m_elapsed / m_anim->frame_length) % m_anim->num_frames;

        m_renderer->getRenderObj(m_render_obj)->setClip((m_cur_frame % m_anim->columns) * m_frame_width, 
                                                        (m_cur_frame / m_anim->columns) * m_frame_height);
        m_elapsed %= m_anim->frame_length;
    }
}

void Diamond::AnimatorSheet::initClip() {
    m_frame_width = m_anim->sprite_sheet->getWidth() / m_anim->columns;
    m_frame_height = m_anim->sprite_sheet->getHeight() / m_anim->rows;

    m_renderer->getRenderObj(m_render_obj)->setClip(0, 0, m_frame_width, m_frame_height);
}

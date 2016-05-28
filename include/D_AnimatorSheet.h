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

#ifndef D_ANIMATOR_SHEET_H
#define D_ANIMATOR_SHEET_H

#include <memory>
#include "D_AnimationSheet.h"
#include "D_Component.h"
#include "D_Renderer2D.h"
#include "D_RenderComponent2D.h"

namespace Diamond {
    class AnimatorSheet : public Component {
    public:
        AnimatorSheet(Renderer2D *renderer, 
                      renderobj_id render_obj, 
                      const AnimationSheet *anim);

        AnimatorSheet(RenderComponent2D *rcomp, 
                      const AnimationSheet *anim);


        void                    setAnimation(const AnimationSheet *anim);
        const AnimationSheet    *getAnimation() const { return m_anim; }
        void                    update(tD_delta delta) override;

    private:
        Renderer2D              *m_renderer;
        renderobj_id            m_render_obj;
        const AnimationSheet    *m_anim;

        int16_t                 m_frame_width, m_frame_height;
        tD_index                m_cur_frame;
        tD_delta                m_elapsed;

        void initClip();
    };
}

#endif // D_ANIMATOR_SHEET_H

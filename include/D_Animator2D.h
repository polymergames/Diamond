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

#ifndef D_ANIMATOR_2D_H
#define D_ANIMATOR_2D_H

#include "D_Animation2D.h"
#include "D_Component.h"
#include "D_RenderComponent2D.h"

namespace Diamond {
    class Animator2D : public Component {
    public:
        Animator2D(RenderComponent2D *rcomp,
                   const Animation2D *anim);


        const Animation2D                   *getAnimation() const { return m_anim; }

        void                                setAnimation(const Animation2D *anim);

        RenderComponent2D                   *getRenderComponent() { return m_render_comp; }
        const RenderComponent2D             *getRenderComponent() const { return m_render_comp; }

        void                                setRenderComponent(RenderComponent2D *rcomp);


        tD_index                            getCurFrame() const { return m_cur_frame; }

        tD_delta                            getCurFrameElapsed() const { return m_elapsed; }


        void                                update(tD_delta delta) override;


    private:
        RenderComponent2D                   *m_render_comp;
        const Animation2D                   *m_anim;

        tD_index                            m_cur_frame;
        tD_delta                            m_elapsed;
    };
}

#endif // D_ANIMATOR_2D_H

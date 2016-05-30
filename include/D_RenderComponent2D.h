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

#ifndef D_RENDER_COMPONENT_2D_H
#define D_RENDER_COMPONENT_2D_H

#include <memory>

#include "D_Component.h"
#include "D_Entity2D.h"
#include "D_Renderer2D.h"
#include "D_Texture.h"

namespace Diamond {
    class RenderComponent2D : public Component {
    public:
        RenderComponent2D(transform2_id transform, 
                          Renderer2D *renderer, 
                          const SharedPtr<const Texture> &sprite)
            : m_transform(transform), m_renderer(renderer), m_sprite(sprite), m_clipDim() {
              m_renderObj = renderer->genRenderObj(transform, sprite);
        }
        ~RenderComponent2D() { freeRenderObj(); }
        
        transform2_id getTransform() const { return m_transform; }
        Renderer2D *getRenderer() const { return m_renderer; }
        renderobj_id getRenderObj() const { return m_renderObj; }

        const SharedPtr<const Texture> &getSprite() const { return m_sprite; }
        void setSprite(const Texture *sprite) { setSprite(SharedPtr<const Texture>(sprite)); }
        void setSprite(const SharedPtr<const Texture> &sprite);

        const Vector2<int> &getClipDim() const { return m_clipDim; }
        void setClip(int x, int y, int w, int h);
        void setClip(int x, int y);

        const Vector2<tDrender_pos> &getPivot() const { return m_pivot; }
        void setPivot(const Vector2<tDrender_pos> &pivot);


        void flipX();
        void flipY();

        int isFlippedX() const;
        int isFlippedY() const;

        // TODO: implement visibility in renderer system, not in rendercomponent
        /**
         Returns whether this game object's sprite is currently being rendered.
        */
        bool isVisible() const;

        /**
         Causes this game object to be rendered.
         This game object must have a sprite (use setSprite() if needed) before calling this function.
        */
        void makeVisible();

        /**
         Causes this game object to stop being rendered.
        */
        void makeInvisible();

        /**
         If this game object is currently visible, makes it invisible (ie not rendered), and vice versa.
        */
        void toggleVisibility();

    private:
        transform2_id m_transform;
        Renderer2D *m_renderer;
        renderobj_id m_renderObj;
        SharedPtr<const Texture> m_sprite;
        Vector2<int> m_clipDim;
        Vector2<tDrender_pos> m_pivot;

        void freeRenderObj();
    };
}

inline void Diamond::RenderComponent2D::setSprite(const SharedPtr<const Texture> &sprite) {
    m_sprite = sprite;
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->setTexture(sprite.get());
    }
}

inline void Diamond::RenderComponent2D::flipX() {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->flipX();
    }
}

inline void Diamond::RenderComponent2D::flipY() {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->flipY();
    }
}

inline int Diamond::RenderComponent2D::isFlippedX() const {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        return m_renderer->getRenderObj(m_renderObj)->isFlippedX();
    }
    else {
        return 0;
    }
}

inline int Diamond::RenderComponent2D::isFlippedY() const {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        return m_renderer->getRenderObj(m_renderObj)->isFlippedY();
    }
    else {
        return 0;
    }
}

inline bool Diamond::RenderComponent2D::isVisible() const {
    return (tD_index)m_renderObj != Diamond::INVALID;
}

inline void Diamond::RenderComponent2D::makeVisible() {
    if ((tD_index)m_renderObj == Diamond::INVALID) {
        m_renderObj = m_renderer->genRenderObj(m_transform, m_sprite, m_pivot);
        if (m_clipDim.x != 0) { // check if any valid clip data has been stored
            RenderObj2D *r = m_renderer->getRenderObj(m_renderObj);
            r->setClip(0, 0, m_clipDim.x, m_clipDim.y);
        }
    }
}

inline void Diamond::RenderComponent2D::makeInvisible() {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->getClipDim(m_clipDim);
        freeRenderObj();
    }
}

inline void Diamond::RenderComponent2D::toggleVisibility() {
    m_renderObj == Diamond::INVALID ? makeVisible() : makeInvisible();
}

inline void Diamond::RenderComponent2D::setPivot(const Vector2<tDrender_pos> &pivot) {
    m_pivot = pivot;
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->setPivot(pivot);
    }
}

inline void Diamond::RenderComponent2D::setClip(int x, int y, int w, int h) {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->setClip(x, y, w, h);
    }
}

inline void Diamond::RenderComponent2D::setClip(int x, int y) {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->getRenderObj(m_renderObj)->setClip(x, y);
    }
}


inline void Diamond::RenderComponent2D::freeRenderObj() {
    if ((tD_index)m_renderObj != Diamond::INVALID) {
        m_renderer->freeRenderObj(m_renderObj);
        m_renderObj = Diamond::INVALID;
    }
}

#endif // D_RENDER_COMPONENT_2D_H

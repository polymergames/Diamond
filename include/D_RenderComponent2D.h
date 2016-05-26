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
                          std::shared_ptr<const Texture> sprite)
            : transform(transform), renderer(renderer), sprite(sprite), clip_dim() {
              render_obj = renderer->genRenderObj(transform, sprite.get());
        }
        ~RenderComponent2D() { freeRenderObj(); }
        
        std::shared_ptr<const Texture> getSprite() const { return sprite; }
        void setSprite(const Texture *sprite) { setSprite(std::shared_ptr<const Texture>(sprite)); }
        void setSprite(std::shared_ptr<const Texture> sprite);

        void flipX();
        void flipY();

        int isFlippedX() const;
        int isFlippedY() const;

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

        const Vector2<tDrender_pos> &getPivot() const { return pivot; }
        void setPivot(const Vector2<tDrender_pos> &pivot);

        void setClip(int x, int y, int w, int h);
        void setClip(int x, int y);

    private:
        transform2_id transform;
        Renderer2D *renderer;
        renderobj_id render_obj;
        std::shared_ptr<const Texture> sprite;
        Vector2<int> clip_dim;
        Vector2<tDrender_pos> pivot;

        void freeRenderObj();
    };
}

inline void Diamond::RenderComponent2D::setSprite(std::shared_ptr<const Texture> sprite) {
    this->sprite = sprite;
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->setTexture(sprite.get());
    }
}

inline void Diamond::RenderComponent2D::flipX() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->flipX();
    }
}

inline void Diamond::RenderComponent2D::flipY() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->flipY();
    }
}

inline int Diamond::RenderComponent2D::isFlippedX() const {
    if ((tD_index)render_obj != Diamond::INVALID) {
        return renderer->getRenderObj(render_obj)->isFlippedX();
    }
    else {
        return 0;
    }
}

inline int Diamond::RenderComponent2D::isFlippedY() const {
    if ((tD_index)render_obj != Diamond::INVALID) {
        return renderer->getRenderObj(render_obj)->isFlippedY();
    }
    else {
        return 0;
    }
}

inline bool Diamond::RenderComponent2D::isVisible() const {
    return (tD_index)render_obj != Diamond::INVALID;
}

inline void Diamond::RenderComponent2D::makeVisible() {
    if ((tD_index)render_obj == Diamond::INVALID) {
        render_obj = renderer->genRenderObj(transform, sprite.get(), pivot);
        if (clip_dim.x != 0) { // check if any valid clip data has been stored
            RenderObj2D *r = renderer->getRenderObj(render_obj);
            r->setClip(0, 0, clip_dim.x, clip_dim.y);
        }
    }
}

inline void Diamond::RenderComponent2D::makeInvisible() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->getClipDim(clip_dim);
        freeRenderObj();
    }
}

inline void Diamond::RenderComponent2D::toggleVisibility() {
    render_obj == Diamond::INVALID ? makeVisible() : makeInvisible();
}

inline void Diamond::RenderComponent2D::setPivot(const Vector2<tDrender_pos> &pivot) {
    this->pivot = pivot;
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->setPivot(pivot);
    }
}

inline void Diamond::RenderComponent2D::setClip(int x, int y, int w, int h) {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->setClip(x, y, w, h);
    }
}

inline void Diamond::RenderComponent2D::setClip(int x, int y) {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->setClip(x, y);
    }
}


inline void Diamond::RenderComponent2D::freeRenderObj() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->freeRenderObj(render_obj);
        render_obj = Diamond::INVALID;
    }
}

#endif // D_RENDER_COMPONENT_2D_H

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
        RenderComponent2D(Entity2D *parent, Texture *sprite, float scale = 1.0f);
        RenderComponent2D(Entity2D *parent, std::shared_ptr<Texture> sprite, float scale = 1.0f);
        ~RenderComponent2D();
        
        std::shared_ptr<Texture> getSprite() const { return sprite; }
        void setSprite(Texture *sprite) { setSprite(std::shared_ptr<Texture>(sprite)); }
        void setSprite(std::shared_ptr<Texture> sprite);

        float getScale() const { return scale; }
        void setScale(float scale);

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

        void initClip();
        void setClip(int x, int y, int w, int h);
        void setClip(int x, int y);

    private:
        std::shared_ptr<Texture> sprite;
        Vector2<int> clip_dim;
        renderobj_id render_obj;
        float scale;
        Renderer2D *renderer;

        void freeRenderObj();
    };
}

inline void Diamond::RenderComponent2D::setSprite(std::shared_ptr<Texture> sprite) {
    this->sprite = sprite;
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->setTexture(sprite.get(), scale);
    }
}

inline void Diamond::RenderComponent2D::setScale(float scale) {
    this->scale = scale;
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->applyScale(scale);
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
        render_obj = renderer->genRenderObj(sprite.get(), parent->getTransformID(), scale);
        if (clip_dim.x != 0) { // check if any valid clip data has been stored
            RenderObj2D *r = renderer->getRenderObj(render_obj);
            r->initClip();
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

inline void Diamond::RenderComponent2D::initClip() {
    if ((tD_index)render_obj != Diamond::INVALID) {
        renderer->getRenderObj(render_obj)->initClip();
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

#endif // D_RENDER_COMPONENT_2D_H

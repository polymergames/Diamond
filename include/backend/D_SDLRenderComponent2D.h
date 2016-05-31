/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef D_SDL_RENDER_COMPONENT_2D_H
#define D_SDL_RENDER_COMPONENT_2D_H

#include <memory>

#include "duSwapVector.h"
#include "D_RenderComponent2D.h"
#include "D_SDLRenderObj2D.h"
#include "D_Texture.h"
#include "D_SDLtypedefs.h"

namespace Diamond {
    class SDLRenderComponent2D : public RenderComponent2D {
    public:
        SDLRenderComponent2D(SDLRenderObjList &renderObjList, SDLrenderobj_id renderObj)
            : m_renderObjList(renderObjList), m_renderObj(renderObj) {}
        ~SDLRenderComponent2D() { m_renderObjList.erase(m_renderObj); }


        SharedPtr<const Texture> getSprite() const override { return m_renderObjList[m_renderObj].texture(); }

        void setSprite(const SharedPtr<const Texture> &sprite) override {
            m_renderObjList[m_renderObj].texture() = std::dynamic_pointer_cast<const SDLTexture>(sprite);
        }


        Vector2<tD_pos> getClipPos() const override {
            SDL_Rect &clip = m_renderObjList[m_renderObj].clip();
            return Vector2<tD_pos>(clip.x, clip.y);
        }

        Vector2<int> getClipDim() const override {
            SDL_Rect &clip = m_renderObjList[m_renderObj].clip();
            return Vector2<int>(clip.w, clip.h);
        }

        void setClip(tD_pos x, tD_pos y, int w, int h) override {
            SDL_Rect &clip = m_renderObjList[m_renderObj].clip();
            clip.x = x;
            clip.y = y;
            clip.w = w;
            clip.h = h;
        }

        void setClipPos(tD_pos x, tD_pos y) override {
            SDL_Rect &clip = m_renderObjList[m_renderObj].clip();
            clip.x = x;
            clip.y = y;
        }

        void setClipDim(int w, int h) override {
            SDL_Rect &clip = m_renderObjList[m_renderObj].clip();
            clip.w = w;
            clip.h = h;
        }

        Vector2<tD_pos> getPivot() const override {
            SDL_Point &pivot = m_renderObjList[m_renderObj].pivot();
            return Vector2<tD_pos>(pivot.x, pivot.y);
        }

        void setPivot(const Vector2<tD_pos> &newpivot) override {
            m_renderObjList[m_renderObj].pivot() = { (int)newpivot.x, (int)newpivot.y };
        }


        void flipX() override { m_renderObjList[m_renderObj].flipX(); }
        void flipY() override { m_renderObjList[m_renderObj].flipY(); }

        bool isFlippedX() const override { return m_renderObjList[m_renderObj].isFlippedX(); }
        bool isFlippedY() const override { return m_renderObjList[m_renderObj].isFlippedY(); }

    private:
        SDLrenderobj_id m_renderObj;
        SDLRenderObjList &m_renderObjList;
    };
}

#endif // D_SDL_RENDER_COMPONENT_2D_H

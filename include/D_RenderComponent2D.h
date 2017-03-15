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

#ifndef D_RENDER_COMPONENT_H
#define D_RENDER_COMPONENT_H

#include "duDumbPtr.h"
#include "duVector2.h"
#include "D_Component.h"
#include "D_Texture.h"
#include "D_typedefs.h"

namespace Diamond {
    class RenderComponent2D : public Component {
    public:
        virtual ~RenderComponent2D() {}


        virtual DumbPtr<Texture>            getSprite() const = 0;

        virtual void                        setSprite(const DumbPtr<Texture> &sprite) = 0;

        virtual RenderLayer                 getLayer() const = 0;
        virtual void                        setLayer(RenderLayer newLayer) = 0;

        virtual Vector2<tD_pos>             getClipPos() const = 0;
        virtual Vector2<int>                getClipDim() const = 0;

        virtual void                        setClip(tD_pos x, tD_pos y, int w, int h) = 0;
        virtual void                        setClipPos(tD_pos x, tD_pos y) = 0;
        virtual void                        setClipDim(int w, int h) = 0;


        virtual Vector2<tD_pos>             getPivot() const = 0;

        virtual void                        setPivot(const Vector2<tD_pos> &newpivot) = 0;


        virtual void                        flipX() = 0;
        virtual void                        flipY() = 0;

        virtual bool                        isFlippedX() const = 0;
        virtual bool                        isFlippedY() const = 0;
    };
}

#endif // D_RENDER_COMPONENT_H

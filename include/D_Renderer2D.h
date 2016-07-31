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

#ifndef D_RENDERER_2D_H
#define D_RENDERER_2D_H

#include <iostream>
#include "duVector2.h"
#include "D_Config.h"
#include "D_RenderComponent2D.h"
#include "D_Texture.h"
#include "D_typedefs.h"

namespace Diamond {

    struct RenderDef2D {
        RenderLayer layer;
        Vector2<tD_pos> pivot;
    };


    class Renderer2D {
    public:
        virtual ~Renderer2D() {}

        virtual bool init(const Config &config) = 0;
        
        virtual void renderAll() = 0;
        
        virtual Vector2<int> getResolution() const = 0;

        virtual Vector2<int> getScreenResolution() const = 0;

        /**
         Loads an image file as a texture.
         Returns nullptr if texture failed to load.
        */
        virtual SharedPtr<Texture> loadTexture(std::string path) = 0;

        
        virtual SharedPtr<RenderComponent2D> makeRenderComponent(
                const DTransform2 &transform,
                const SharedPtr<const Texture> &texture,
                RenderLayer layer = 0,
                const Vector2<tD_pos> &pivot = Vector2<tD_pos>(0, 0)
        ) = 0;

        SharedPtr<RenderComponent2D> makeRenderComponent(
                const ConstTransform2Ptr &transform,
                const SharedPtr<const Texture> &texture,
                RenderLayer layer = 0,
                const Vector2<tD_pos> &pivot = Vector2<tD_pos>(0, 0)
        ) {
            return makeRenderComponent(*transform, texture, layer, pivot);
        }


        virtual SharedPtr<RenderComponent2D> makeRenderComponent(
                const DTransform2 &transform,
                const SharedPtr<const Texture> &texture,
                const RenderDef2D &renderDef
        ) {
            return makeRenderComponent(transform, texture,
                                       renderDef.layer, renderDef.pivot);
        }

        SharedPtr<RenderComponent2D> makeRenderComponent(
                const ConstTransform2Ptr &transform,
                const SharedPtr<const Texture> &texture,
                const RenderDef2D &renderDef
        ) {
            return makeRenderComponent(transform, texture,
                                       renderDef.layer, renderDef.pivot);
        }
        
        
        // Primitives rendering
        virtual void renderPoint(const Vector2<tD_pos> &coords,
                                 const RGBA &color) = 0;
        
        virtual void renderLine(const Vector2<tD_pos> &p1,
                                const Vector2<tD_pos> &p2,
                                const RGBA &color) = 0;
    };
}

#endif // D_RENDERER_2D_H

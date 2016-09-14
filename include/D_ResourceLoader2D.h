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

#ifndef D_RESOURCE_LOADER2D_H
#define D_RESOURCE_LOADER2D_H

#include <unordered_map>
#include "D_AnimationSheet.h"
#include "D_ConfigTable.h"
#include "D_PhysicsWorld2D.h"
#include "D_Renderer2D.h"
#include "D_TextureFactory.h"


namespace Diamond {
    /**
     * These functions construct resource definitions
     * from configuration tables. The resource definitions
     * can in turn be used to construct Diamond components.
     *
     * The functions return true if a valid definition was stored
     * in the output parameter, otherwise they return false.
     */
    class ResourceLoader2D {
    public:
        bool loadRenderDef(const ConfigTable &config,
                           RenderDef2D &renderDef,
                           std::string &texturePath,
                           Vector2<tD_real> &scale) const;

        bool loadAABBDef(const ConfigTable &config,
                         AABBDef2D &aabb) const;

        bool loadCircleDef(const ConfigTable &config,
                           CircleDef &circle) const;

        bool loadAnimationSheet(const ConfigTable &config, 
                                TextureFactory &textureFactory, 
                                AnimationSheet &animationSheet) const;


        PointList2D loadPoints(const ConfigTable &config) const;


        ConfigTable genRenderConfig(
                const RenderDef2D &renderDef,
                const std::string &texturePath,
                const Vector2<tD_real> &scale = Vector2<tD_real>(1, 1)
        ) const;

        ConfigTable genAABBConfig(const AABBDef2D &aabb) const;

        ConfigTable genCircleConfig(const CircleDef &circle) const;

        ConfigTable genPointsConfig(const PointList2D &points) const;
        
    protected:
        bool loadColliderDef(const ConfigTable &config,
                             ColliderDef2D &collider) const;
    };
}

#endif // D_RESOURCE_LOADER2D_H

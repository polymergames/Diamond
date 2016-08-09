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

#ifndef D_DEBUG_DRAWER_H
#define D_DEBUG_DRAWER_H

#include "D_Renderer2D.h"
#include "D_PhysicsWorld2D.h"
#include "D_typedefs.h"

namespace Diamond {
    class DebugDrawer {
    public:

        static constexpr float DEFAULT_ANGLE_INTERVAL = 12.0f;

        DebugDrawer(Renderer2D *renderer);

        // Polygons

        void draw(const PointList2D &poly, const RGBA &color);

        void draw(const PolyCollider *poly, const RGBA &color) {
            // DEBUG
            for (auto point : poly->worldPoints())
                std::cout << point << std::endl;

            draw(poly->worldPoints(), color);
        }
        
        void draw(const SharedPtr<PolyCollider> &poly, const RGBA &color) {
            draw(poly.get(), color);
        }

        // Circles

        void draw(const CircleDef &circle,
                  const RGBA &color,
                  float angleInterval = DEFAULT_ANGLE_INTERVAL);

        void draw(const CircleCollider *circle,
                  const RGBA &color,
                  float angleInterval = DEFAULT_ANGLE_INTERVAL);

        void draw(const SharedPtr<CircleCollider> &circle,
                  const RGBA &color,
                  float angleInterval = DEFAULT_ANGLE_INTERVAL) {
            draw(circle.get(), color, angleInterval);
        }

    private:
        Renderer2D *m_renderer;
    };
}

#endif // D_DEBUG_DRAWER_H

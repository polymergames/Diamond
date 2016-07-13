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
#include "D_PolyCollider.h"
#include "D_typedefs.h"

namespace Diamond {
    class DebugDrawer {
    public:
        DebugDrawer(Renderer2D *renderer);
        
        void draw(const PolyCollider *poly, const RGBA &color);
        
        void draw(const SharedPtr<PolyCollider> &poly, const RGBA &color) {
            draw(poly.get(), color);
        }
        
    private:
        Renderer2D *m_renderer;
    };
}

#endif // D_DEBUG_DRAWER_H

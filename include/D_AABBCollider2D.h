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

#ifndef D_AABB_COLLIDER_2D_H
#define D_AABB_COLLIDER_2D_H

#include "D_typedefs.h"
#include "D_Vector2.h"

namespace Diamond {
    class AABBCollider2D {
    public:
        virtual ~AABBCollider2D() {}
        
        /**
         Get the origin point of this AABB in the parent transform's local space.
        */
        virtual Vector2<tD_pos> getOrigin() const = 0;
        
        /**
         Get the horizontal x vertical dimensions of this AABB.
        */
        virtual Vector2<tD_pos> getDims() const = 0;
        
        /**
         Get the current coordinates of this AABB's bottom left corner in world space.
        */
        virtual Vector2<tD_pos> getMin() const = 0;
        
        /**
         Get the current coordinates of this AABB's top right corner in world space.
        */
        virtual Vector2<tD_pos> getMax() const = 0;
        
        /**
         Set the origin point of this AABB in the parent transform's local space.
        */
        virtual void setOrigin(const Vector2<tD_pos> &origin) = 0;
        
        /**
         Set the horizontal x vertical dimensions of this AABB.
        */
        virtual void setDims(const Vector2<tD_pos> &dims) = 0;
    };
}

#endif // D_AABB_COLLIDER_2D_H

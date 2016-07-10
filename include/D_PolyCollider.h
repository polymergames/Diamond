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

#ifndef D_POLY_COLLIDER_H
#define D_POLY_COLLIDER_H

#include <vector>
#include "duVector2.h"
#include "D_Collider2D.h"
#include "D_typedefs.h"

namespace Diamond {
    /**
     Should only be used for convex shapes.
    */
    class PolyCollider : public Collider2D {
    public:
        virtual ~PolyCollider() {}
        
        /**
         Get the coordinates of this polygon's vertices
         in the parent rigidbody's local space.
        */
        virtual PointList points() const = 0;
        
        /**
         Get the current coordinates of this polygon's vertices
         in world space.
        */
        virtual PointList worldPoints() const = 0;
    };
}

#endif // D_POLY_COLLIDER_H

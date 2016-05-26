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

#ifndef D_CIRCLE_COLLIDER_H
#define D_CIRCLE_COLLIDER_H

#include "D_Collider2D.h"
#include "D_typedefs.h"
#include "duVector2.h"

namespace Diamond {
    class CircleCollider : public Collider2D {
    public:
        virtual ~CircleCollider() {}
        
        /**
         Get the radius of this circle.
        */
        virtual tD_pos getRadius() const = 0;
        
        /**
         Get the radius squared of this circle.
        */
        virtual tD_pos getRadiusSq() const = 0;
        
        /**
         Get the center position of this circle in the parent transform's local space.
        */
        virtual Vector2<tD_pos> getCenter() const = 0;
        
        /**
         Get the current coordinates of this circle's center in world space.
        */
        virtual Vector2<tD_pos> getWorldPos() const = 0;
        
        virtual void setRadius(tD_pos radius) = 0;
        
        virtual void setCenter(const Vector2<tD_pos> &center) = 0;
    };
}

#endif // D_CIRCLE_COLLIDER_H

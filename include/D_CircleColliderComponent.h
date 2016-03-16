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

#ifndef D_CIRCLE_COLLIDER_COMPONENT_H
#define D_CIRCLE_COLLIDER_COMPONENT_H

#include "D_ColliderComponent2D.h"
#include "D_Vector2.h"
#include "Q_CircleCollider.h"

namespace Diamond {
    class CircleColliderComponent : public ColliderComponent2D {
    public:
        CircleColliderComponent(Entity2D *parent,
                                std::function<void(Entity2D *other)> &onCollision,
                                tD_pos radius,
                                const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0));

        /**
         Get the radius of this circle.
        */
        tD_pos getRadius() const { return circle->getRadius(); }

        /**
         Get the radius squared of this circle.
        */
        tD_long_pos getRadiusSq() const { return circle->getRadiusSq(); }

        /**
         Get the center position of this circle in the parent transform's local space.
        */
        Diamond::Vector2<tD_pos> &getCenter() { return circle->getCenter(); }

        /**
         Get the current coordinates of this circle's center in world space.
        */
        const Diamond::Vector2<tD_pos> &getWorldPos() const { return circle->getWorldPos(); }

        void setRadius(tD_pos radius) { circle->setRadius(radius); }

        void setCenter(const Diamond::Vector2<tD_pos> &center) { circle->setCenter(center); }

    private:
        Quantum2D::CircleCollider *circle;
    };
}

#endif // D_CIRCLE_COLLIDER_COMPONENT_H

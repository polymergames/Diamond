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

#ifndef Q_CIRCLE_COLLIDER_H
#define Q_CIRCLE_COLLIDER_H

#include "Q_Collider2D.h"
#include "D_Vector2.h"

namespace Quantum2D {
    class CircleCollider : public Collider2D {
    public:
        CircleCollider(body2d_id body,
                       void *parent,
                       std::function<void(void *other)> &onCollision,
                       tQ_pos radius,
                       const Diamond::Vector2<tQ_pos> &center = Diamond::Vector2<tQ_pos>(0, 0));

        /**
         Get the radius of this circle.
        */
        tQ_pos getRadius() const { return radius; }

        /**
         Get the radius squared of this circle.
        */
        tQ_pos getRadiusSq() const { return radiusSq; }

        /**
         Get the center position of this circle in the parent transform's local space.
        */
        Diamond::Vector2<tQ_pos> &getCenter() { return center; }

        /**
         Get the current coordinates of this circle's center in world space.
        */
        const Diamond::Vector2<tQ_pos> &getWorldPos() const { return world_pos; }

        void setRadius(tQ_pos radius) { this->radius = radius; radiusSq = radius * radius; }

        void setCenter(const Diamond::Vector2<tQ_pos> &center) { this->center = center; }

        /**
         Update world coordinates, should call this once per frame.
        */
        void update(tQ_delta delta_ms, Diamond::Transform2<tQ_pos, tQ_rot> &trans) override;

    private:
        tQ_pos radius;
        tQ_pos radiusSq;
        Diamond::Vector2<tQ_pos> center;
        Diamond::Vector2<tQ_pos> world_pos;
    };
}

#endif // Q_CIRCLE_COLLIDER_H

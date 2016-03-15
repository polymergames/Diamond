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

#ifndef D_AABB_COLLIDER_COMPONENT_2D_H
#define D_AABB_COLLIDER_COMPONENT_2D_H

#include "D_ColliderComponent2D.h"
#include "D_Vector2.h"
#include "Q_AABBCollider2D.h"
#include "Q_QuantumWorld2D.h"

namespace Diamond {
    class AABBColliderComponent2D : public ColliderComponent2D {
    public:
        AABBColliderComponent2D(Entity2D *parent, 
                                std::function<void(Entity2D *other)> &onCollision, 
                                const Vector2<tD_pos> &dims, 
                                const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0));

        /**
        Get the current coordinates of this AABB's bottom left corner in world space.
        */
        const Vector2<tD_pos> &getMin() const { return aabb->getMin(); }

        /**
        Get the current coordinates of this AABB's top right corner in world space.
        */
        const Vector2<tD_pos> &getMax() const { return aabb->getMax(); }

        /**
        Get the origin point of this AABB in the parent transform's local space.
        */
        const Vector2<tD_pos> &getOrigin() { return aabb->getOrigin(); }

        /**
        Get the horizontal x vertical dimensions of this AABB.
        */
        const Vector2<tD_pos> &getDims() { return aabb->getDims(); }

        void setOrigin(const Vector2<tD_pos> &origin) { aabb->setOrigin(origin); }

        void setDims(const Vector2<tD_pos> &dims) { aabb->setDims(dims); }

    private:
        Quantum2D::AABBCollider2D *aabb;
    };
}

#endif // D_AABB_COLLIDER_COMPONENT_2D_H
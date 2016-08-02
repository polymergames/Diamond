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

#ifndef D_PHYSICS_WORLD_2D_H
#define D_PHYSICS_WORLD_2D_H

#include <functional>
#include "D_Config.h"
#include "D_CircleCollider.h"
#include "D_AABBCollider2D.h"
#include "D_PolyColPoints.h"
#include "D_PolyCollider.h"
#include "D_Rigidbody2D.h"
#include "D_typedefs.h"

namespace Diamond {

    struct RigidbodyDef2D {
        // TODO: mass, etc.
    };

    struct AABBDef2D {
        Vector2<tD_pos> dims = Vector2<tD_pos>(1, 1);
        Vector2<tD_pos> origin;
    };

    struct CircleDef {
        tD_pos radius = 1;
        Vector2<tD_pos> center;
    };


    class PhysicsWorld2D {
    public:
        virtual ~PhysicsWorld2D() {}

        /**
         * Creates and initializes the physics simulation world.
         * Returns true if initialization was successful.
         */
        virtual bool init(const Config &config) = 0;

        /**
         * Steps the physics simulation by the number of milliseconds given
         * and syncs physics and Diamond transform data.
         */
        virtual void update(tD_delta delta_ms) = 0;
        
        /**
         * Creates a rigidbody object attached to the given transform.
         */
        virtual SharedPtr<Rigidbody2D> makeRigidbody(DTransform2 &transform) = 0;

        SharedPtr<Rigidbody2D> makeRigidbody(const Transform2Ptr &transform) {
            return makeRigidbody(*transform);
        }

        
        /**
         * Creates an AABB collider attached to the given rigidbody.
         * parent is a pointer to the object owning the collider.
         */
        virtual SharedPtr<AABBCollider2D> makeAABBCollider(
                const SharedPtr<Rigidbody2D> &body,
                void *parent,
                const std::function<void(void *other)> &onCollision,
                const Vector2<tD_pos> &dims,
                const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)
        ) = 0;

        SharedPtr<AABBCollider2D> makeAABBCollider(
                const SharedPtr<Rigidbody2D> &body,
                void *parent,
                const std::function<void(void *other)> &onCollision,
                const AABBDef2D &colDef
        ) {
            return makeAABBCollider(body, parent, onCollision,
                                    colDef.dims, colDef.origin);
        }


        /**
         * Creates a circle collider attached to the given rigidbody.
         * parent is a pointer to the object owning the collider.
         */
        virtual SharedPtr<CircleCollider> makeCircleCollider(
                const SharedPtr<Rigidbody2D> &body,
                void *parent,
                const std::function<void(void *other)> &onCollision,
                tD_pos radius,
                const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0)
        ) = 0;

        SharedPtr<CircleCollider> makeCircleCollider(
                const SharedPtr<Rigidbody2D> &body,
                void *parent,
                const std::function<void(void *other)> &onCollision,
                const CircleDef &colDef
        ) {
            return makeCircleCollider(body, parent, onCollision,
                                      colDef.radius, colDef.center);
        }


        /**
         * Transforms the given set of points into the physics engine's
         * required format for polygon collider points. The given
         * and returned points are in local space, and the
         * returned object should be used to construct polygon colliders
         * with the given shape.
         */
        virtual SharedPtr<PolyColPoints> makePolyColPoints(const PointList2D &points) = 0;
        
        /**
         * Creates a polygon collider attached to the given rigidbody.
         * parent is a pointer to the object owning the collider.
         * The given points may be used by reference
         * and must therefore remain valid throughout the life of the collider.
         */
        virtual SharedPtr<PolyCollider> makePolyCollider(
                const SharedPtr<Rigidbody2D> &body,
                void *parent,
                const std::function<void(void *other)> &onCollision,
                const SharedPtr<PolyColPoints> &points
        ) = 0;
    };
}

#endif // D_PHYSICS_WORLD_2D_H

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
#include "D_Rigidbody2D.h"
#include "D_typedefs.h"

namespace Diamond {
    class PhysicsWorld2D {
    public:
        virtual ~PhysicsWorld2D() {}

        /**
         Creates and initializes the physics simulation world.
         Returns true if initialization was successful.
        */
        virtual bool init(const Config &config) = 0;

        /**
         Steps the physics simulation by the number of milliseconds given.
        */
        virtual void step(tD_delta delta_ms) = 0;

        /**
         Updates the game's transforms with the data from the physics engine's rigidbodies.
        */
        virtual void updateTransforms() = 0;

        /**
         Updates the physics engine's rigidbodies with the data from the game's transforms.
        */
        virtual void updateBodies() = 0;
        
        /**
         Creates a rigidbody object attached to the given transform.
        */
        virtual Rigidbody2D *genRigidbody(transform2_id transform) = 0;
        
        /**
         Frees the memory associated with the given rigidbody.
        */
        virtual void freeRigidbody(Rigidbody2D *body) = 0;

        
        /**
         Creates an AABB collider attached to the given rigidbody.
         parent is a pointer to the object owning the collider.
        */
        virtual AABBCollider2D *genAABBCollider(const Rigidbody2D *body,
                                                void *parent,
                                                const std::function<void(void *other)> &onCollision,
                                                const Vector2<tD_pos> &dims,
                                                const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)) = 0;

        /**
         Creates a circle collider attached to the given rigidbody.
         parent is a pointer to the object owning the collider.
        */
        virtual CircleCollider *genCircleCollider(const Rigidbody2D *body,
                                                  void *parent,
                                                  const std::function<void(void *other)> &onCollision,
                                                  tD_pos radius,
                                                  const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0)) = 0;

        /**
         Frees the memory associated with a given collider.
        */
        virtual void freeCollider(Collider2D *collider) = 0;
    };
}

#endif // D_PHYSICS_WORLD_2D_H

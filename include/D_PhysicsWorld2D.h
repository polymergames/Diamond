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

#include "D_Config.h"
#include "D_Rigidbody2D.h"
#include "D_typedefs.h"
#include "D_Transform2.h"

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
         Creates a transform object and returns its id.
        */
        virtual transform2_id genTransform() = 0;

        /**
         Frees the given transform's memory.
        */
        virtual void freeTransform(transform2_id transform) = 0;

        /**
         Creates a rigidbody object attached to the given transform.
        */
        virtual DRigidbody2D *genRigidbody(transform2_id transform) = 0;

        /**
         Frees the given rigidbody's memory.
        */
        virtual void freeRigidbody(DRigidbody2D *body) = 0;

        /**
         Returns the transform with the given id.
        */
        virtual Transform2<tD_pos, tD_rot> getTransform(transform2_id transform) = 0;

        /**
         Sets the transform with the given id.
        */
        virtual void setTransform(transform2_id transform, const Transform2<tD_pos, tD_rot> &newtrans) = 0;

        /**
         Sets the transform with the given id.
        */
        virtual void setTransform(transform2_id transform, const Vector2<tD_pos> &newpos, tD_rot newrot) = 0;

        /**
         Sets the position of the given transform.
        */
        virtual void setPosition(transform2_id transform, const Vector2<tD_pos> &newpos) = 0;

        /**
         Sets the rotation of the given transform.
        */
        virtual void setRotation(transform2_id transform, tD_rot newrot) = 0;
    };
}

#endif // D_PHYSICS_WORLD_2D_H

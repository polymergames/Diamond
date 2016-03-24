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

#include "D_Rigidbody2D.h"
#include "D_typedefs.h"
#include "D_Vector2.h"

namespace Diamond {
    class PhysicsWorld2D {
    public:
        PhysicsWorld2D() {}
        virtual ~PhysicsWorld2D() {}

        /**
         Returns the position of the given transform.
        */
        virtual Vector2<tD_pos> getPosition(transform2_id transform) = 0;

        /**
         Sets the position of the given transform.
        */
        virtual void setPosition(transform2_id transform, Vector2<tD_pos> newpos) = 0;

        /**
         Returns the rotation of the given transform.
        */
        virtual tD_rot getRotation(transform2_id transform) = 0;

        /**
         Sets the rotation of the given transform.
        */
        virtual void setRotation(transform2_id transform, tD_rot newrot) = 0;

        /**
         Creates a Rigidbody2D object attached to the given transform.
        */
        virtual Rigidbody2D *genRigidbody(transform2_id transform) = 0;
    };
}

#endif // D_PHYSICS_WORLD_2D_H

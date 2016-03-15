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

#ifndef Q_COLLISION_TEST_2D_H
#define Q_COLLISION_TEST_2D_H

#include "Q_AABBCollider2D.h"

namespace Quantum2D {
    namespace CollisionTest2D {
        /**
         Initializes the collision tester.
         Returns true if initialization was successful, otherwise false.
        */
        bool init();

        bool collide(Collider2D *a, Collider2D *b);

        bool AABB2(AABBCollider2D *a, AABBCollider2D *b);
    }
}

#endif // Q_COLLISION_TEST_2D_H

/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef Q_DYNAMIC_WORLD_2D_H
#define Q_DYNAMIC_WORLD_2D_H

#include "Q_Collider2D.h"
#include "Q_Rigidbody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    struct ColliderPair {
    public:
        ColliderPair(Collider2D *a, Collider2D *b) : a(a), b(b) {}

        Collider2D *a, *b;
    };


    class DynamicWorld2D {
    public:
        /**
         Initializes the simulation world.
         Returns true if initialization was successful, otherwise false.
        */
        bool init();


        /**
         Returns a reference to the rigidbody with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
         Only use this reference immediately after calling this function!
        */
        Rigidbody2D &getRigidbody(body2d_id body) { return bodies[body]; }
        const Rigidbody2D &getRigidbody(body2d_id body) const { return bodies[body]; }

        /**
         Creates a rigidbody object attached to the given transform and returns its id.
         The returned id can be used to access the rigidbody with getRigidbody(id).
        */
        body2d_id genRigidbody() { return bodies.emplace_back(); }

        /**
         Frees the given rigidbody's memory.
        */
        void freeRigidbody(body2d_id body) { bodies.erase(body); }


        /**
         Returns a pointer to the collider with the given id.
        */
        Collider2D *getCollider(collider2_id collider) { return colliders[collider].get(); }
        const Collider2D *getCollider(collider2_id collider) const { return colliders[collider].get(); }

        /**
         Creates a 2D collider object of the given type using the given constructor arguments 
         and adds it to the collision detection system.
         NOTE: the first constructor argument of all collider types, bodylist, is provided.
         You only need to call this function with the subsequent arguments.
         The returned id can be used to access the collider with getCollider(id).
        */
        template <class T, typename... Args>
        collider2_id genCollider(Args&&... args) {
            return colliders.emplace_back(new T(bodies, std::forward<Args>(args)...));
        }

        /**
         Adds a collider to the collision detection system.
         The owner of the given pointer should now be QuantumWorld2D!
         The returned id can be used to access the collider with getCollider(id).
        */
        collider2_id addCollider(Collider2D *col) { return colliders.emplace_back(col); }

        /**
         Frees the given collider's memory.
        */
        void freeCollider(collider2_id collider) { colliders.erase(collider); }


        /**
         Steps the physics simulation by the number of milliseconds given.
        */
        void step(tQ_delta delta);

        /**
         Get the pairs of colliders that collided in the last simulation step.
        */
        const std::vector<ColliderPair> &getCollidePairs() { return pairs; }

        /**
		 Invokes callback functions for this frame's collision pairs.
        */
		void callbackCollisions();

    private:
        BodyList bodies;
        ColliderList colliders;

        std::vector<ColliderPair> pairs;
    };
}

#endif // Q_DYNAMIC_WORLD_2D_H

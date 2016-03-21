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

#ifndef Q_QUANTUM_WORLD_2D_H
#define Q_QUANTUM_WORLD_2D_H

#include <memory>

#include "D_Transform2.h"
#include "D_sparsevector.h"
#include "D_swapvector.h"
#include "Q_Collider2D.h"
#include "Q_Rigidbody2D.h"

#include "Q_typedefs.h"

namespace Quantum2D {
    namespace QuantumWorld2D {
        
        extern Diamond::sparsevector<Diamond::Transform2<tQ_pos, tQ_rot> > transforms;
        extern Diamond::swapvector<Rigidbody2D> bodies;
        extern Diamond::swapvector<std::unique_ptr<Collider2D> > colliders;
        
        /**
        Initializes the simulation world.
        Returns true if initialization was successful, otherwise false.
        */
        bool init();

        /**
         Returns a reference to the transform with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
         Only use this reference immediately after calling this function!
        */
        inline Diamond::Transform2<tQ_pos, tQ_rot> &getTransform(transform2_id transform) {
            return transforms[transform];
        }
        
        /**
         Returns a reference to the rigidbody with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new rigidbody is created.
         Only use this reference immediately after calling this function!
        */
        inline Rigidbody2D &getRigidbody(body2d_id body) {
            return bodies[body];
        }
        
        /**
         Returns a pointer to the collider with the given id.
        */
        inline Collider2D *getCollider(collider2_id collider) {
            return colliders[collider].get();
        }
        
        
        /**
         Creates a Transform2i object and returns its id.
         The returned id can be used to access the transform with getTransform(id).
        */
        inline transform2_id genTransform() {
            return transforms.emplace_back();
        }
        
        /**
         Frees the given index in transforms as available for a new Transform2i
        */
        inline void freeTransform(transform2_id transform) {
            transforms.erase(transform);
        }
        
        
        /**
         Creates a Rigidbody2D object attached to the given transform and returns its id.
         The returned id can be used to access the rigidbody with getRigidbody(id).
        */
        inline body2d_id genRigidbody(transform2_id transform) {
            return bodies.emplace_back(transform);
        }
        
        /**
         Marks the given id as available for a new Rigidbody2D, 
         and removes its currently associated rigidbody.
        */
        inline void freeRigidbody(body2d_id body) {
            bodies.erase(body);
        }
        
        
        /**
         Creates a 2D collider object of the given type using the given constructor arguments.
         The returned id can be used to access the collider with getCollider(id).
        */
        template <class T, typename... Args>
        inline collider2_id genCollider(Args&&... args) {
            return colliders.emplace_back(new T(std::forward<Args>(args)...));
        }
                      
        /**
         Adds a collider to the collision detection system.
         The owner of the given pointer should now be QuantumWorld2D!
         The returned id can be used to access the collider with getCollider(id).
        */
        inline collider2_id addCollider(Collider2D *col) {
            return colliders.emplace_back(col);
        }
        
        /**
         Marks the given id as available for a new Collider2D, 
         and destroys its currently associated collider.
        */
        inline void freeCollider(collider2_id collider) {
            colliders.erase(collider);
        }
        
        
        /**
         Steps the physics simulation by the number of milliseconds given.
        */
        void step(tQ_delta delta_ms);
    }
}

#endif // Q_QUANTUM_WORLD_2D_H

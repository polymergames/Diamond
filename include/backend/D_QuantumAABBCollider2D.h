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

#ifndef D_QUANTUM_AABB_COLLIDER_2D_H
#define D_QUANTUM_AABB_COLLIDER_2D_H

#include <functional>
#include "D_AABBCollider2D.h"
#include "D_QuantumBody2D.h"
#include "D_typedefs.h"
#include "Q_AABBCollider2D.h"

namespace Diamond {
    class QuantumAABBCollider2D : public AABBCollider2D {
    public:
        QuantumAABBCollider2D(QuantumBody2D* body,
                              void *parent, 
                              Quantum2D::DynamicWorld2D *world, 
                              std::function<void(void *other)> &onCollision, 
                              const Vector2<tD_pos> &dims,
                              const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)) : world(world) {
            aabb = new Quantum2D::AABBCollider2D(body->getID(), parent, onCollision, dims, origin);
            collider = world->addCollider(aabb);
        }
        
        ~QuantumAABBCollider2D() { world->freeCollider(collider); }
        
        Vector2<tD_pos> getOrigin() const override { return aabb->getOrigin(); }
        
        Vector2<tD_pos> getDims() const override { return aabb->getDims(); }
        
        Vector2<tD_pos> getMin() const override { return aabb->getMin(); }
        
        Vector2<tD_pos> getMax() const override { return aabb->getMax(); }
        
        void setOrigin(const Vector2<tD_pos> &origin) override { aabb->setOrigin(origin); }
        
        void setDims(const Vector2<tD_pos> &dims) override { aabb->setDims(dims); }
    
    private:
        collider2_id collider;
        Quantum2D::AABBCollider2D *aabb;
        Quantum2D::DynamicWorld2D *world;
    };
}

#endif // D_QUANTUM_AABB_COLLIDER_2D_H

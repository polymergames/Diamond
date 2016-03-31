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
#include "Q_QuantumWorld2D.h"
#include "Q_AABBCollider2D.h"

namespace Diamond {
    class QuantumAABBCollider2D : public AABBCollider2D {
    public:
        QuantumAABBCollider2D(QuantumBody2D *body,
                              void *parent,
                              std::function<void(void *other)> &onCollision,
                              const Vector2<tQ_pos> &dims,
                              const Vector2<tQ_pos> &origin = Vector2<tQ_pos>(0, 0)) {
            // TODO: use rigidbody instead of transform to construct collider
            transform2_id transform = Quantum2D::QuantumWorld2D::getRigidbody(body->getID()).getTransformID();
            aabb = new Quantum2D::AABBCollider2D(transform, parent, onCollision, dims, origin);
            collider = Quantum2D::QuantumWorld2D::addCollider(aabb);
        }
        
        ~QuantumAABBCollider2D() { Quantum2D::QuantumWorld2D::freeCollider(collider); }
        
        Vector2<tD_pos> getOrigin() const override { aabb->getOrigin(); }
        
        Vector2<tD_pos> getDims() const override { aabb->getDims(); }
        
        Vector2<tD_pos> getMin() const override { aabb->getMin(); }
        
        Vector2<tD_pos> getMax() const override { aabb->getMax(); }
        
        void setOrigin(const Vector2<tD_pos> &origin) override { aabb->setOrigin(origin); }
        
        void setDims(const Vector2<tD_pos> &dims) override { aabb->setDims(dims); }
    
    private:
        collider2_id collider;
        Quantum2D::AABBCollider2D *aabb;
    };
}

#endif // D_QUANTUM_AABB_COLLIDER_2D_H

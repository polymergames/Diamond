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
#include "Q_AABBCollider2D.h"

namespace Diamond {
    class QuantumAABBCollider2D : public AABBCollider2D {
    public:
        QuantumAABBCollider2D(collider2_id collider, Quantum2D::AABBCollider2D *aabb) 
            : collider(collider), aabb(aabb) {}
        ~QuantumAABBCollider2D() {}

        // TODO: Make a QuantumCollider base class with collider ID and colFunc functions!
        collider2_id getColliderID() const { return collider; }
        
        CollisionLayer getLayer() const override {
            return aabb->getLayer();
        }
        
        void setLayer(CollisionLayer layer) override {
            aabb->setLayer(layer);
        }
        
        void setColFunc(const std::function<void(void *other)> &onCollision) override {
            aabb->setColFunc(onCollision);
        }
        
        Vector2<tD_pos> getOrigin() const override { return aabb->getOrigin(); }
        
        Vector2<tD_pos> getDims() const override { return aabb->getDims(); }
        
        Vector2<tD_pos> getMin() const override { return aabb->getMin(); }
        
        Vector2<tD_pos> getMax() const override { return aabb->getMax(); }
        
        void setOrigin(const Vector2<tD_pos> &origin) override { aabb->setOrigin(origin); }
        
        void setDims(const Vector2<tD_pos> &dims) override { aabb->setDims(dims); }
    
    private:
        collider2_id collider;
        Quantum2D::AABBCollider2D *aabb;
    };
}

#endif // D_QUANTUM_AABB_COLLIDER_2D_H

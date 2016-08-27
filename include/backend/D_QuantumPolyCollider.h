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

#ifndef D_QUANTUM_POLY_COLLIDER_H
#define D_QUANTUM_POLY_COLLIDER_H

#include <functional>
#include "D_PolyCollider.h"
#include "Q_PolyCollider.h"

namespace Diamond {
    class QuantumPolyCollider : public PolyCollider {
    public:
        QuantumPolyCollider(collider2_id collider, Quantum2D::PolyCollider *poly)
            : collider(collider), poly(poly) {}
        ~QuantumPolyCollider() {}
        
        collider2_id getColliderID() const { return collider; }
        
        CollisionLayer getLayer() const override {
            return poly->getLayer();
        }
        
        void setLayer(CollisionLayer layer) override {
            poly->setLayer(layer);
        }
        
        void setColFunc(const std::function<void(void *other)> &onCollision) override {
            poly->setColFunc(onCollision);
        }
        
        PointList2D points() const override { return poly->points(); }
        
        PointList2D worldPoints() const override { return poly->worldPoints(); }
        
    private:
        collider2_id collider;
        Quantum2D::PolyCollider *poly;
    };
}

#endif // D_QUANTUM_POLY_COLLIDER_H

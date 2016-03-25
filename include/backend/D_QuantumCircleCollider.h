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

#ifndef D_QUANTUM_CIRCLE_COLLIDER_H
#define D_QUANTUM_CIRCLE_COLLIDER_H

#include <functional>
#include "D_CircleCollider.h"
#include "D_QuantumBody2D.h"
#include "D_typedefs.h"
#include "Q_QuantumWorld2D.h"
#include "Q_CircleCollider.h"

namespace Diamond {
    class QuantumCircleCollider : public CircleCollider {
    public:
        QuantumCircleCollider(QuantumBody2D *body,
                              void *parent,
                              std::function<void(void *other)> &onCollision,
                              tQ_pos radius,
                              const Vector2<tQ_pos> &center = Vector2<tQ_pos>(0, 0)) {
            // TODO: use rigidbody instead of transform to construct collider
            transform2_id transform = Quantum2D::QuantumWorld2D::getRigidbody(body->getID()).getTransformID();
            circle = new Quantum2D::CircleCollider(transform, parent, onCollision, radius, center);
            collider = Quantum2D::QuantumWorld2D::addCollider(circle);
        }
        
        ~QuantumCircleCollider() {
            Quantum2D::QuantumWorld2D::freeCollider(collider);
        }
        
        tD_pos getRadius() const { return circle->getRadius(); }
        
        tD_pos getRadiusSq() const { return circle->getRadiusSq(); }
        
        Vector2<tD_pos> getCenter() const { return circle->getCenter(); }
        
        Vector2<tD_pos> getWorldPos() const { return circle->getWorldPos(); }
        
        void setRadius(tD_pos radius) { circle->setRadius(radius); }
        
        void setCenter(const Vector2<tD_pos> &center) { circle->setCenter(center); }
        
    private:
        collider2_id collider;
        Quantum2D::CircleCollider *circle;
    };
}

#endif // D_QUANTUM_CIRCLE_COLLIDER_H

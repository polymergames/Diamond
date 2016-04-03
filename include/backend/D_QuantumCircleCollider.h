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
#include "Q_CircleCollider.h"

namespace Diamond {
    class QuantumCircleCollider : public CircleCollider {
    public:
        QuantumCircleCollider(QuantumBody2D *body,
                              void *parent, 
                              Quantum2D::DynamicWorld2D *world, 
                              std::function<void(void *other)> &onCollision,
                              tQ_pos radius,
                              const Vector2<tQ_pos> &center = Vector2<tQ_pos>(0, 0)) : world(world) {
            circle = new Quantum2D::CircleCollider(body->getID(), parent, onCollision, radius, center);
            collider = world->addCollider(circle);
        }
        
        ~QuantumCircleCollider() { world->freeCollider(collider); }
        
        tD_pos getRadius() const override { return circle->getRadius(); }
        
        tD_pos getRadiusSq() const override { return circle->getRadiusSq(); }
        
        Vector2<tD_pos> getCenter() const override { return circle->getCenter(); }
        
        Vector2<tD_pos> getWorldPos() const override { return circle->getWorldPos(); }
        
        void setRadius(tD_pos radius) override { circle->setRadius(radius); }
        
        void setCenter(const Vector2<tD_pos> &center) override { circle->setCenter(center); }
        
    private:
        collider2_id collider;
        Quantum2D::CircleCollider *circle;
        Quantum2D::DynamicWorld2D *world;
    };
}

#endif // D_QUANTUM_CIRCLE_COLLIDER_H

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

#ifndef D_QUANTUM_WORLD_2D_H
#define D_QUANTUM_WORLD_2D_H

#include "D_PhysicsWorld2D.h"
#include "D_QuantumBody2D.h"
#include "D_QuantumAABBCollider2D.h"
#include "D_QuantumCircleCollider.h"

namespace Diamond {
    // TODO: use instanced QuantumWorld object
    class DQuantumWorld2D : public PhysicsWorld2D {
    public:
        DQuantumWorld2D() {} // TODO: create QuantumWorld object or set to nullptr

        ~DQuantumWorld2D() {
            // TODO: free QuantumWorld instance
        }

        bool init(const Config &config) override {
            return Quantum2D::QuantumWorld2D::init();
        }

        void step(tD_delta delta_ms) override {
            Quantum2D::QuantumWorld2D::step(delta_ms);
        }
        

        transform2_id genTransform() override {
            return Quantum2D::QuantumWorld2D::genTransform();
        }

        void freeTransform(transform2_id transform) override {
            Quantum2D::QuantumWorld2D::freeTransform(transform);
        }
        

        DRigidbody2D *genRigidbody(transform2_id transform) override {
            return new QuantumBody2D(transform);
        }
        
        
        AABBCollider2D *genAABBCollider(DRigidbody2D *body,
                                        void *parent,
                                        std::function<void(void *other)> &onCollision,
                                        const Vector2<tD_pos> &dims,
                                        const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)) override {
            return new QuantumAABBCollider2D(dynamic_cast<QuantumBody2D*>(body), parent, onCollision, dims, origin);
        }
        
        CircleCollider *genCircleCollider(DRigidbody2D *body,
                                          void *parent,
                                          std::function<void(void *other)> &onCollision,
                                          tD_pos radius,
                                          const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0)) override {
            return new QuantumCircleCollider(dynamic_cast<QuantumBody2D*>(body), parent, onCollision, radius, center);
        }
        

        Transform2<tD_pos, tD_rot> getTransform(transform2_id transform) override {
            return Quantum2D::QuantumWorld2D::getTransform(transform);
        }

        void setTransform(transform2_id transform, const Transform2<tD_pos, tD_rot> &newtrans) override {
            Quantum2D::QuantumWorld2D::getTransform(transform) = newtrans;
        }

        void setTransform(transform2_id transform, const Vector2<tD_pos> &newpos, tD_rot newrot) override {
            Transform2<tQ_pos, tQ_rot> &tr = Quantum2D::QuantumWorld2D::getTransform(transform);
            tr.position = newpos;
            tr.rotation = newrot;
        }

        void setPosition(transform2_id transform, const Vector2<tD_pos> &newpos) override {
            Quantum2D::QuantumWorld2D::getTransform(transform).position = newpos;
        }

        void setRotation(transform2_id transform, tD_rot newrot) override {
            Quantum2D::QuantumWorld2D::getTransform(transform).rotation = newrot;
        }
    };
}

#endif // D_QUANTUM_WORLD_2D_H

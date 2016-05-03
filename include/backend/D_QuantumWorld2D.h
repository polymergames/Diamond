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

#include <map>
#include "D_PhysicsWorld2D.h"
#include "D_QuantumBody2D.h"
#include "D_QuantumAABBCollider2D.h"
#include "D_QuantumCircleCollider.h"
#include "Q_DynamicWorld2D.h"

namespace Diamond {
    class QuantumWorld2D : public PhysicsWorld2D {
    public:
        QuantumWorld2D() : data(nullptr) {}

        bool init(const Config &config, DataCenter *data) override {
            this->data = data;
            return world.init(); 
        }

        void step(tD_delta delta_ms) override { world.step(delta_ms); }
        
        void updateTransforms() override {
            for (auto i = pairs.begin(); i != pairs.end(); ++i) {
                Quantum2D::Rigidbody2D &rbody = world.getRigidbody(i->first);
                Transform2<tD_pos, tD_rot> &trans = data->getTransform(i->second);
                trans.position = rbody.getPosition();
                trans.rotation = rbody.getRotation();
            }
        }

        void updateBodies() override {
            for (auto i = pairs.begin(); i != pairs.end(); ++i) {
                Quantum2D::Rigidbody2D &rbody = world.getRigidbody(i->first);
                Transform2<tD_pos, tD_rot> &trans = data->getTransform(i->second);
                rbody.setPosition(trans.position);
                rbody.setRotation(trans.rotation);
            }
        }

        Rigidbody2D *genRigidbody(transform2_id transform) override {
            QuantumBody2D *body = new QuantumBody2D(&world);
            pairs[body->getID()] = transform;
            return body;
        }

        void freeRigidbody(Rigidbody2D *body) override {
            QuantumBody2D *qbody = dynamic_cast<QuantumBody2D*>(body);
            if (qbody) {
                pairs.erase(qbody->getID());
                delete qbody;
            }
        }
        
        
        AABBCollider2D *genAABBCollider(const Rigidbody2D *body,
                                        void *parent,
                                        const std::function<void(void *other)> &onCollision,
                                        const Vector2<tD_pos> &dims,
                                        const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)) override {
            const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body);
            if (qbody) {
                collider2_id col = world.genCollider<Quantum2D::AABBCollider2D>(qbody->getID(), parent, onCollision, dims, origin);
                Quantum2D::AABBCollider2D *aabb = dynamic_cast<Quantum2D::AABBCollider2D*>(world.getCollider(col));
                if (aabb)
                    return new QuantumAABBCollider2D(col, aabb);
            }
            return nullptr;
        }
        
        CircleCollider *genCircleCollider(const Rigidbody2D *body,
                                          void *parent,
                                          const std::function<void(void *other)> &onCollision,
                                          tD_pos radius,
                                          const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0)) override {
            const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body);
            if (qbody) {
                collider2_id col = world.genCollider<Quantum2D::CircleCollider>(qbody->getID(), parent, onCollision, radius, center);
                Quantum2D::CircleCollider *circle = dynamic_cast<Quantum2D::CircleCollider*>(world.getCollider(col));
                if (circle)
                    return new QuantumCircleCollider(col, circle);
            }
            return nullptr;
        }

        void freeCollider(Collider2D *collider) override {
            // Try aabb
            QuantumAABBCollider2D *qaabb = dynamic_cast<QuantumAABBCollider2D*>(collider);
            if (qaabb) {
                world.freeCollider(qaabb->getColliderID());
                return;
            }

            // try circle
            QuantumCircleCollider *qcircle = dynamic_cast<QuantumCircleCollider*>(collider);
            if (qcircle) {
                world.freeCollider(qcircle->getColliderID());
                return;
            }
        }

    private:
        Quantum2D::DynamicWorld2D world;
        DataCenter *data;
        std::map<body2d_id, transform2_id> pairs;
    };
}

#endif // D_QUANTUM_WORLD_2D_H

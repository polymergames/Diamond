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
#include "Q_DynamicWorld2D.h"
#include "D_PhysicsWorld2D.h"
#include "D_QuantumBody2D.h"
#include "D_QuantumAABBCollider2D.h"
#include "D_QuantumCircleCollider.h"
#include "D_Transform2.h"

namespace Diamond {
    class QuantumBodyDeleter {
    public:
        QuantumBodyDeleter(std::map<body2d_id, DTransform2*> &pairs) : m_pairs(pairs) {}

        void operator() (Rigidbody2D *body) const {
            QuantumBody2D *qbody = dynamic_cast<QuantumBody2D*>(body);
            if (qbody) {
                m_pairs.erase(qbody->getID());
            }
            delete body;
            // DEBUG
            // Log::log("Quantumbody deleted");
        }

    private:
        std::map<body2d_id, DTransform2*> &m_pairs;
    };


    class QuantumColliderDeleter {
    public:
        QuantumColliderDeleter(Quantum2D::DynamicWorld2D &world) : m_world(world) {}

        void operator() (Collider2D *collider) const {
            QuantumAABBCollider2D *qaabb = nullptr;
            QuantumCircleCollider *qcircle = nullptr;

            // Try aabb
            if (qaabb = dynamic_cast<QuantumAABBCollider2D*>(collider))
                m_world.freeCollider(qaabb->getColliderID());
            // try circle
            else if (qcircle = dynamic_cast<QuantumCircleCollider*>(collider))
                m_world.freeCollider(qcircle->getColliderID());

            delete collider;
            // DEBUG
            // Log::log("QuantumCollider deleted");
        }
    private:
        Quantum2D::DynamicWorld2D &m_world;
    };


    // TODO: get rid of dynamic allocation, in this and other classes, and just return IDs
    // (or ID containers) ex. in makeRigidbody, etc.
    // or use memory pools
    class QuantumWorld2D : public PhysicsWorld2D {
    public:
        QuantumWorld2D() : m_bodyDeleter(m_pairs), m_colliderDeleter(m_world) {}

        bool init(const Config &config) override { return m_world.init(); }

        void update(tD_delta delta_ms) override { 
            updateBodies();
            
            m_world.step(delta_ms);
            
            // Sync diamond transforms with physics transforms
            // BEFORE calling collision callbacks
            // in case the collision callbacks make any changes to
            // diamond transforms which would then be lost
            // if syncing transforms was done afterwards.
            updateTransforms();
            
            m_world.callbackCollisions();
        }
        
        void updateBodies() {
            for (auto i = m_pairs.begin(); i != m_pairs.end(); ++i) {
                Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(i->first);
                rbody.setPosition(i->second->position);
                rbody.setRotation(i->second->rotation);
            }
        }

        void updateTransforms() {
            for (auto i = m_pairs.begin(); i != m_pairs.end(); ++i) {
                Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(i->first);
                i->second->position = rbody.getPosition();
                // TODO: test!
                i->second->rotation = rbody.getRotation();
            }
        }
        

        SharedPtr<Rigidbody2D> makeRigidbody(DTransform2 &transform) override {
            QuantumBody2D *body = new QuantumBody2D(&m_world);

            // Add to rigibody-entity pairs so they can be synchronized
            m_pairs[body->getID()] = &transform;

            // Initialize the new rigidbody with the parent entity's world transform
            Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(body->getID());
            rbody.setPosition(transform.position);
            rbody.setRotation(transform.rotation);
            return SharedPtr<Rigidbody2D>(body, m_bodyDeleter);
        }
        
        
        SharedPtr<AABBCollider2D> makeAABBCollider(const SharedPtr<Rigidbody2D> &body,
                                                   void *parent,
                                                   const std::function<void(void *other)> &onCollision,
                                                   const Vector2<tD_pos> &dims,
                                                   const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0)) override {
            const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body.get());
            if (qbody) {
                collider2_id col = m_world.genCollider<Quantum2D::AABBCollider2D>(qbody->getID(), parent, onCollision, dims, origin);
                Quantum2D::AABBCollider2D *aabb = dynamic_cast<Quantum2D::AABBCollider2D*>(m_world.getCollider(col));
                if (aabb)
                    return SharedPtr<AABBCollider2D>(new QuantumAABBCollider2D(col, aabb), m_colliderDeleter);
            }
            return nullptr;
        }
        
        SharedPtr<CircleCollider> makeCircleCollider(const SharedPtr<Rigidbody2D> &body,
                                                     void *parent,
                                                     const std::function<void(void *other)> &onCollision,
                                                     tD_pos radius,
                                                     const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0)) override {
            const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body.get());
            if (qbody) {
                collider2_id col = m_world.genCollider<Quantum2D::CircleCollider>(qbody->getID(), parent, onCollision, radius, center);
                Quantum2D::CircleCollider *circle = dynamic_cast<Quantum2D::CircleCollider*>(m_world.getCollider(col));
                if (circle)
                    return SharedPtr<CircleCollider>(new QuantumCircleCollider(col, circle), m_colliderDeleter);
            }
            return nullptr;
        }

    private:
        Quantum2D::DynamicWorld2D m_world;
        std::map<body2d_id, DTransform2*> m_pairs;

        QuantumBodyDeleter m_bodyDeleter;
        QuantumColliderDeleter m_colliderDeleter;
    };
}

#endif // D_QUANTUM_WORLD_2D_H

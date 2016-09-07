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

#include "D_QuantumWorld2D.h"


Diamond::QuantumBodyDeleter::QuantumBodyDeleter(MemPool<QuantumBody2D>            &bodyPool,
                                                std::map<body2d_id, DTransform2*> &pairs)
    : m_bodyPool(bodyPool), 
      m_pairs(pairs) {}


void Diamond::QuantumBodyDeleter::operator() (Rigidbody2D *body) const {
    QuantumBody2D *qbody = dynamic_cast<QuantumBody2D*>(body);

    if (qbody) {
        m_pairs.erase(qbody->getID());
        m_bodyPool.free(qbody);

        // DEBUG
        // Log::log("Quantumbody deleted");
    }
}


Diamond::QuantumColliderDeleter::QuantumColliderDeleter(Quantum2D::DynamicWorld2D      &world, 
                                                        MemPool<QuantumAABBCollider2D> &aabbPool, 
                                                        MemPool<QuantumCircleCollider> &circlePool,
                                                        MemPool<QuantumPolyCollider>   &polyPool)
    : m_world(world),
      m_aabbPool(aabbPool),
      m_circlePool(circlePool),
      m_polyPool(polyPool) {}


void Diamond::QuantumColliderDeleter::operator() (Collider2D *collider) const {
    QuantumAABBCollider2D *qaabb = nullptr;
    QuantumCircleCollider *qcircle = nullptr;
    QuantumPolyCollider *qpoly = nullptr;

    // TODO: create a base quantum collider class
    // and use it to get the collider ID,
    // don't need these conditionals

    // Try aabb
    if (qaabb = dynamic_cast<QuantumAABBCollider2D*>(collider)) {
        m_world.freeCollider(qaabb->getColliderID());
        m_aabbPool.free(qaabb);
    }
    // try circle
    else if (qcircle = dynamic_cast<QuantumCircleCollider*>(collider)) {
        m_world.freeCollider(qcircle->getColliderID());
        m_circlePool.free(qcircle);
    }
    // try poly
    else if (qpoly = dynamic_cast<QuantumPolyCollider*>(collider)) {
        m_world.freeCollider(qpoly->getColliderID());
        m_polyPool.free(qpoly);
    }
    // DEBUG
    // Log::log("QuantumCollider deleted");
}


Diamond::QuantumWorld2D::QuantumWorld2D()
// TODO: construct collider pools with estimates of how many of each collider max can be onscreen at a time!
// and same for body pool
    : m_bodyPool(200),
      m_aabbPool(100), 
      m_circlePool(100), 
      m_polyPool(100),
      m_bodyDeleter(m_bodyPool, m_pairs),
      m_colliderDeleter(m_world, m_aabbPool, m_circlePool, m_polyPool) {}


void Diamond::QuantumWorld2D::update(tD_delta delta_ms) {
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


void Diamond::QuantumWorld2D::updateBodies() {
    for (auto i = m_pairs.begin(); i != m_pairs.end(); ++i) {
        Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(i->first);
        rbody.position() = i->second->position;
        rbody.rotation() = i->second->rotation;
    }
}


void Diamond::QuantumWorld2D::updateTransforms() {
    for (auto i = m_pairs.begin(); i != m_pairs.end(); ++i) {
        Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(i->first);
        i->second->position = rbody.position();
        // TODO: test!
        i->second->rotation = rbody.rotation();
    }
}


Diamond::SharedPtr<Diamond::Rigidbody2D> Diamond::QuantumWorld2D::makeRigidbody(DTransform2 &transform) {
    QuantumBody2D *body = m_bodyPool.make(&m_world);

    // Add to rigibody-entity pairs so they can be synchronized
    m_pairs[body->getID()] = &transform;

    // Initialize the new rigidbody with the given transform
    Quantum2D::Rigidbody2D &rbody = m_world.getRigidbody(body->getID());
    rbody.position() = transform.position;
    rbody.rotation() = transform.rotation;
    return SharedPtr<Rigidbody2D>(body, m_bodyDeleter);
}


Diamond::SharedPtr<Diamond::AABBCollider2D> Diamond::QuantumWorld2D::makeAABBCollider(
    const SharedPtr<Rigidbody2D> &body,
    void *parent,
    const std::function<void(void *other)> &onCollision,
    const Vector2<tD_pos> &dims,
    const Vector2<tD_pos> &origin,
    CollisionLayer layer
) {
    const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body.get());
    if (qbody) {
        collider2_id col = m_world.genCollider<Quantum2D::AABBCollider2D>(qbody->getID(),
                                                                          parent,
                                                                          onCollision,
                                                                          dims,
                                                                          origin,
                                                                          layer);
        Quantum2D::AABBCollider2D *aabb = dynamic_cast<Quantum2D::AABBCollider2D*>(m_world.getCollider(col));
        if (aabb)
            return SharedPtr<AABBCollider2D>(m_aabbPool.make(col, aabb),
                m_colliderDeleter);
    }
    return nullptr;
}


Diamond::SharedPtr<Diamond::CircleCollider> Diamond::QuantumWorld2D::makeCircleCollider(
    const SharedPtr<Rigidbody2D> &body,
    void *parent,
    const std::function<void(void *other)> &onCollision,
    tD_pos radius,
    const Vector2<tD_pos> &center,
    CollisionLayer layer
) {
    const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body.get());
    if (qbody) {
        collider2_id col = m_world.genCollider<Quantum2D::CircleCollider>(qbody->getID(),
                                                                          parent,
                                                                          onCollision,
                                                                          radius,
                                                                          center,
                                                                          layer);
        Quantum2D::CircleCollider *circle = dynamic_cast<Quantum2D::CircleCollider*>(m_world.getCollider(col));
        if (circle)
            return SharedPtr<CircleCollider>(m_circlePool.make(col, circle),
                                             m_colliderDeleter);
    }
    return nullptr;
}


Diamond::SharedPtr<Diamond::PolyCollider> Diamond::QuantumWorld2D::makePolyCollider(
    const SharedPtr<Rigidbody2D> &body,
    void *parent,
    const std::function<void(void *other)> &onCollision,
    const PointList2D &points,
    CollisionLayer layer
) {
    const QuantumBody2D *qbody = dynamic_cast<const QuantumBody2D*>(body.get());
    if (qbody) {
        collider2_id col = m_world.genCollider<Quantum2D::PolyCollider>(qbody->getID(),
                                                                        parent,
                                                                        onCollision,
                                                                        points,
                                                                        layer);
        Quantum2D::PolyCollider *poly = dynamic_cast<Quantum2D::PolyCollider*>(m_world.getCollider(col));
        if (poly)
            return SharedPtr<PolyCollider>(m_polyPool.make(col, poly),
                                           m_colliderDeleter);
    }
    return nullptr;
}

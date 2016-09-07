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
#include "duMemPool.h"
#include "Q_DynamicWorld2D.h"
#include "D_PhysicsWorld2D.h"
#include "D_QuantumBody2D.h"
#include "D_QuantumAABBCollider2D.h"
#include "D_QuantumCircleCollider.h"
#include "D_QuantumPolyCollider.h"
#include "D_Transform2.h"

namespace Diamond {
    class QuantumBodyDeleter {
    public:
        QuantumBodyDeleter(MemPool<QuantumBody2D>            &bodyPool,
                           std::map<body2d_id, DTransform2*> &pairs);

        void operator() (Rigidbody2D *body) const;

    private:
        MemPool<QuantumBody2D>            &m_bodyPool;
        std::map<body2d_id, DTransform2*> &m_pairs;
    };


    class QuantumColliderDeleter {
    public:
        QuantumColliderDeleter(Quantum2D::DynamicWorld2D      &world, 
                               MemPool<QuantumAABBCollider2D> &aabbPool, 
                               MemPool<QuantumCircleCollider> &circlePool,
                               MemPool<QuantumPolyCollider>   &polyPool) ;

        void operator() (Collider2D *collider) const;

    private:
        Quantum2D::DynamicWorld2D      &m_world;

        MemPool<QuantumAABBCollider2D> &m_aabbPool;
        MemPool<QuantumCircleCollider> &m_circlePool;
        MemPool<QuantumPolyCollider>   &m_polyPool;
    };


    class QuantumWorld2D : public PhysicsWorld2D {
    public:
        QuantumWorld2D();

        bool init(const Config &config) override { return m_world.init(); }
        

        void setLayersCollide(CollisionLayer layer1,
                              CollisionLayer layer2,
                              bool collides) override {
            m_world.setLayersCollide(layer1, layer2, collides);
        }
        
        bool doLayersCollide(CollisionLayer layer1,
                             CollisionLayer layer2) const override {
            return m_world.doLayersCollide(layer1, layer2);
        }
        
        
        void allLayersCollideOn() override { m_world.allLayersCollideOn(); }
        
        void allLayersCollideOff() override { m_world.allLayersCollideOff(); }
        
        
        void update(tD_delta delta_ms) override;
        
        void updateBodies();

        void updateTransforms();
        

        SharedPtr<Rigidbody2D> makeRigidbody(DTransform2 &transform) override;
        
        
        SharedPtr<AABBCollider2D> makeAABBCollider(const SharedPtr<Rigidbody2D> &body,
                                                   void *parent,
                                                   const std::function<void(void *other)> &onCollision,
                                                   const Vector2<tD_pos> &dims,
                                                   const Vector2<tD_pos> &origin = Vector2<tD_pos>(0, 0),
                                                   CollisionLayer layer = 0) override;
        

        SharedPtr<CircleCollider> makeCircleCollider(const SharedPtr<Rigidbody2D> &body,
                                                     void *parent,
                                                     const std::function<void(void *other)> &onCollision,
                                                     tD_pos radius,
                                                     const Vector2<tD_pos> &center = Vector2<tD_pos>(0, 0),
                                                     CollisionLayer layer = 0) override;

        
        SharedPtr<PolyCollider> makePolyCollider(const SharedPtr<Rigidbody2D> &body,
                                                 void *parent,
                                                 const std::function<void(void *other)> &onCollision,
                                                 const PointList2D &points,
                                                 CollisionLayer layer = 0) override;

    private:
        Quantum2D::DynamicWorld2D         m_world;
        std::map<body2d_id, DTransform2*> m_pairs;

        // Rigidbody pool
        MemPool<QuantumBody2D>            m_bodyPool;

        // Collider pools
        MemPool<QuantumAABBCollider2D>    m_aabbPool;
        MemPool<QuantumCircleCollider>    m_circlePool;
        MemPool<QuantumPolyCollider>      m_polyPool;

        // Deleters
        QuantumBodyDeleter                m_bodyDeleter;
        QuantumColliderDeleter            m_colliderDeleter;
    };
}

#endif // D_QUANTUM_WORLD_2D_H

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

#include "D_AABBColliderComponent2D.h"
#include "D_Entity2D.h"
#include "Q_QuantumWorld2D.h"

Diamond::AABBColliderComponent2D::AABBColliderComponent2D(Entity2D *parent,
                                                          std::function<void(Entity2D *other)> &onCollision,
                                                          const Vector2<tQ_pos> &dims,
                                                          const Vector2<tQ_pos> &origin)
    : ColliderComponent2D(parent, onCollision) {
    std::function<void(void*)> callback = std::bind(&AABBColliderComponent2D::onCollide, this, std::placeholders::_1);
    aabb = new Quantum2D::AABBCollider2D(parent->getTransformID(), parent, callback, dims, origin);
    collider = Quantum2D::QuantumWorld2D::addCollider(aabb);
}

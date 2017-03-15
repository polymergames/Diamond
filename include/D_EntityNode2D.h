/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef D_ENTITY_NODE2D_H
#define D_ENTITY_NODE2D_H

#include "D_Entity.h"
#include "D_Node2D.h"

namespace Diamond {
    /**
     Combines the functionality of an entity-component system and a scene graph node.
     Yeah that's right, we used multiple inheritance. Fight me.
    */
    class EntityNode2D : public Entity, public Node2D {
    public:
        EntityNode2D(const Transform2Ptr &world_transform)
            : Node2D(*world_transform), m_transform(world_transform) {}

        // Entity is responsible for managing the lifetime of a given transform
        virtual ~EntityNode2D() { m_transform.free(); }

        // Since superclass's (Entity's) copy constructor is deleted,
        // a default one is not automatically created here

        // Move!
        EntityNode2D(EntityNode2D &&other)
            : Entity(std::move(other)),
              Node2D(std::move(other)),
              m_transform(other.m_transform) {
            other.m_transform = nullptr;
        }
        // doesn't work because Node2D's assignment operator is deleted
        // EntityNode2D& operator=(EntityNode2D &&other) {
        //     if (this != &other) {
        //         Entity::operator=(std::move(other));
        //         Node2D::operator=(std::move(other));
        //         m_transform.free();
        //         m_transform = other.m_transform;
        //         other.m_transform = nullptr;
        //     }
        // }

        const Transform2Ptr &getTransformPtr() {
            return m_transform;
        }

        // const ConstTransform2Ptr &getTransformPtr() const {
        //     return m_transform;
        // }

    protected:
        Transform2Ptr m_transform;
    };
}

#endif // D_ENTITY_NODE2D_H
